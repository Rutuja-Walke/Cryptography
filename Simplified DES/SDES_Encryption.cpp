/*==========================================
 Title:  Simplified DES Encryption
 Author: Rutuja Sunil Walke
 Date:   1 April 2021
========================================== */


#include <bits/stdc++.h>
using namespace std;


vector<int> pt; //plain text
vector<int> key3; //subkey k1
vector<int> fk;  // subkey k2
vector<int> sw1; // result of first sw 
vector<int> sw2; // result of first sw2 
vector<int> cipher;


//create the S-boxes
int s_zero[4][4] = { {1,0,3,2},
                     {3,2,1,0},
                     {0,2,1,3},
                     {3,1,3,2}};

int s_one[4][4] = { {0,1,2,3},
                    {2,0,1,3},
                    {3,0,1,0},
                    {2,1,0,3}};


vector<int> left_shift(vector<int> &arr, int shift_by)
{
	while (shift_by--)
	{
		int temp = arr[0];
		for (int i = 0; i < 4; i++)
		{
			arr[i] = arr[i+1];
		}		
		arr[4] = temp;
	}
    return arr;
}


int BinarytoDecimal(int a, int b)
{
    //left most bit 2^0 = 1
    //right most bit 2^1 =2
    int digit = (a*2) + (b*1);
    return digit;
}


vector<int> decimaltoBinary(int temp)
{
    vector<int> t;
    if(temp == 3)
        t = {1,1};
 
    else if(temp == 2)
         t = {1,0};
  
    else if(temp == 1)
        t = {0,1};
 
    else
        t = {0,0};

    return t;    
}


vector<int> x_or(vector<int> &a, vector<int> &b)
{
    vector<int> result;
    for(int i=0; i<b.size();i++)
    {
        int temp = a[i] ^ b[i];
        result.push_back(temp);
    }
    return result;
}


void print_fun(vector<int> &arr, int size)
{
    for(int i=0; i<size; i++)
        cout<<arr[i]<<" ";
}

void key_generation(vector<int> &key)
{    
    vector<int> p10 {3,5,2,7,4,10,1,9,8,6};
    vector<int> key2;

    //performing key permutation
    for(int i=0; i<10; i++)
    {
        int x = key[p10[i]-1];
        key2.push_back(x);
    }

    cout<<"\n10 bit key after performing permuation:\n";
    print_fun(key2, key2.size());

    //splitting into 5 bits
    //and performing LS-1
    vector<int> k1;
    vector<int> k2;

    for(int i=0; i<5; i++)
    {
        k1.push_back(key2[i]);
        k2.push_back(key2[i+5]);
    }
 
    k1 = left_shift(k1, 1);
    k2 = left_shift(k2, 1);  

    //append LS-1 keys
    vector<int> k3;
    for(int i=0; i<5; i++)
    {
        k3.push_back(k1[i]);
    }
    for(int i=0; i<5; i++)
    {
        k3.push_back(k2[i]);
    }

    cout<<"\n\n10 bit key after performing LS-1:\n";
    print_fun(k3, k3.size());
    
    vector<int> p8 {6,3,7,4,8,5,10,9};   
    cout<<endl;
    //performing key permutation 
    //result is subkey K1
    for(int i=0; i<8; i++)
    {
        int x = k3[p8[i]-1];
        key3.push_back(x);
    }

    cout<<"\n8 bit subkey k1:\n";
    print_fun(key3, key3.size());    

    //performing LS-2 operation on 10 bits key
    //perform LS-2 on K1 and k2
    vector<int> kk1 = left_shift(k1, 2);
    vector<int> kk2 = left_shift(k2, 2);

    //append LS-2 keys
    vector<int> kk3;
    for(int i=0; i<5; i++)
        kk3.push_back(kk1[i]); 

    for(int i=0; i<5; i++)
        kk3.push_back(kk2[i]);
    

    cout<<"\n\n10 bit key after performing LS-2:\n";
    print_fun(kk3, kk3.size());    
    cout<<endl;

    //performing key permutation 
    //result is subkey K2 (8 bits key)
    for(int i=0; i<8; i++)
    {
        int x = kk3[p8[i]-1];
        fk.push_back(x);
    }
    cout<<"\n8 bit subkey k2:\n";
    print_fun(fk, fk.size());
  
}


vector<int> name_thisfun(vector<int> &pt)
{
    vector<int> p {2,6,3,1,4,8,5,7};
    vector<int> IP;

    //performing initial permutation
    for(int i=0; i<p.size() ; i++)
    {
        int temp = pt[p[i]-1];
        IP.push_back(temp);
    }

    cout<<"\n\nInitial Permutation (IP):\n";
    print_fun(IP, IP.size());
    return IP;
}
    

vector<int> sw1_operation(vector<int> &IP)
{
    //dividing IP into left part & right part
    vector<int> ipl;
    vector<int> ipr; //to be used for E/P

    for(int i=0; i< 4; i++)
    {
        ipl.push_back(IP[i]);
        ipr.push_back(IP[i+4]);
    }

    cout<<endl;
    cout<<"\nLeft 4 IP bits: ";
    print_fun(ipl, ipl.size());
    cout<<endl;
    cout<<"Right 4 IP bits: ";
    print_fun(ipr, ipr.size()); 

    //performing E/P on ipr
    vector<int> EP {4,1,2,3,2,3,4,1};
    vector<int> iprEP; 
    for(int i=0; i<EP.size(); i++)
    {
        int x = ipr[EP[i]-1];
        iprEP.push_back(x);
    }
    
    cout<<"\n\nE/P on right 4-bit:\n";
    print_fun(iprEP, iprEP.size());


    //Xor with subkey k1(i.e key3)
    vector<int> res = x_or(iprEP, key3);

    cout<<"\n\nXor on E/P:\n";
    print_fun(res, res.size());

    //find s-box result based on res
   
    int r1 = BinarytoDecimal(res[0], res[3]); // 1st and 4th bit
    int c1 = BinarytoDecimal(res[1], res[2]);

    int x = s_zero[r1][c1]; //s0 output, convert this to binary

    int r2 = BinarytoDecimal(res[4], res[7]); //for s1
    int c2 = BinarytoDecimal(res[5], res[6]);

    int y = s_one[r2][c2]; //s1 output, convert this to binary
    vector<int> ss0 = decimaltoBinary(x);
    vector<int> ss1 = decimaltoBinary(y);

   /* cout<<"\n\n\n"<<x<<" "<<y;

    cout<<"\n\n\n";
    print_fun(ss0, ss0.size());
    cout<<"\n\n\n";
    print_fun(ss1, ss1.size()); */

    vector<int> s_res;
    for(int i=0; i<2; i++)
    {
        s_res.push_back(ss0[i]);
    }
    for(int i=0; i<2; i++)
    {
        s_res.push_back(ss1[i]);
    }

    cout<<"\n\n\n";
    print_fun(s_res, s_res.size());

    //p4 on s_res
    int arr[4] = {2,4,3,1};
    vector<int> p4;
    for(int i=0; i<4; i++)
    {
        int var = s_res[arr[i]-1];
        p4.push_back(var);
    }

    cout<<"\n\n\n";
    print_fun(p4, p4.size());

    //xor with left 4 bits of IP i.e ipl
    vector<int> left = x_or(p4, ipl);
    
   /* cout<<"\n\n\n";
    print_fun(left, left.size()); */

    //vector<int> sw1;
    for(int i=0; i<4; i++)
    {
        sw1.push_back(ipr[i]);
    }
    for(int i=0; i<4; i++)
    {
        sw1.push_back(left[i]);
    }

    cout<<"\n\nSwap 1:\n";
    print_fun(sw1, sw1.size());

    return left;
}



vector<int> sw2_operation(vector<int> &IP)
{
    //dividing IP into left part & right part
    vector<int> ipl;
    vector<int> ipr; //to be used for E/P

    for(int i=0; i< 4; i++)
    {
        ipl.push_back(IP[i]);
        ipr.push_back(IP[i+4]);
    }

    cout<<endl;
    cout<<"\nLeft 4 IP bits: ";
    print_fun(ipl, ipl.size());
    cout<<endl;
    cout<<"Right 4 IP bits: ";
    print_fun(ipr, ipr.size()); 

    //performing E/P on ipr
    vector<int> EP {4,1,2,3,2,3,4,1};
    vector<int> iprEP; 
    for(int i=0; i<EP.size(); i++)
    {
        int x = ipr[EP[i]-1];
        iprEP.push_back(x);
    }
    
    cout<<"\n\nE/P on left 4-bit:\n";
    print_fun(iprEP, iprEP.size());


    //Xor with subkey k2(i.e fk)
    vector<int> res = x_or(iprEP, fk);

    cout<<"\n\nXor on E/P:\n";
    print_fun(res, res.size());

    //find s-box result based on res
   
    int r1 = BinarytoDecimal(res[0], res[3]);
    int c1 = BinarytoDecimal(res[1], res[2]);

    int x = s_zero[r1][c1]; //s0 output, convert this to binary

    int r2 = BinarytoDecimal(res[4], res[7]);
    int c2 = BinarytoDecimal(res[5], res[6]);

    int y = s_one[r2][c2]; //s1 output, convert this to binary
    vector<int> ss0 = decimaltoBinary(x);
    vector<int> ss1 = decimaltoBinary(y);

    cout<<"\n\n\n"<<x<<" "<<y;

    cout<<"\n\n\n";
    print_fun(ss0, ss0.size());
    cout<<"\n\n\n";
    print_fun(ss1, ss1.size());

    vector<int> s_res;
    for(int i=0; i<2; i++)
    {
        s_res.push_back(ss0[i]);
    }
    for(int i=0; i<2; i++)
    {
        s_res.push_back(ss1[i]);
    }

    cout<<"\n\n\n";
    print_fun(s_res, s_res.size());

    //p4 on s_res
    int arr[4] = {2,4,3,1};
    vector<int> p4;
    for(int i=0; i<4; i++)
    {
        int var = s_res[arr[i]-1];
        p4.push_back(var);
    }

    cout<<"\n\n\n";
    print_fun(p4, p4.size());

    //xor with left 4 bits of IP i.e ipl
    vector<int> left = x_or(p4, ipl);
    
    cout<<"\n\n\n";
    print_fun(left, left.size());

    //vector<int> sw1;
    for(int i=0; i<4; i++)
    {
        sw2.push_back(left[i]);
    }
    for(int i=0; i<4; i++)
    {
        sw2.push_back(ipr[i]);
    }

    cout<<"\n\nRound 2 Result:\n";
    print_fun(sw2, sw2.size());

    return sw2;
}


void encrypt_text(vector<int> &p)
{
    vector<int> ip_inverse {4,1,3,5,7,2,8,6};
    for(int i=0; i<p.size(); i++)
    {
        int temp = p[ip_inverse[i]-1];
        cipher.push_back(temp);
    }
    cout<<"\n\nCIPHER TEXT:";
    print_fun(cipher, cipher.size());
}


int main()
{

    cout<<"Enter 8 bit plain text:\n";
    for(int i=0; i<8; i++)
    {
        int x;
        cin>>x;
        pt.push_back(x);
    }

    vector<int> key;
    cout<<"\n\nEnter 10 bit key:\n";
    for(int i=0; i<10; i++)
    {
        int x;
        cin>>x;
        key.push_back(x);
    }

    cout<<"\n10 bit key:\n";
    print_fun(key, key.size());
    cout<<endl;

    //generates subkey k1 & k2
    key_generation(key); 
    vector<int> ini_permu = name_thisfun(pt); // IP
    vector<int> swap =sw1_operation(ini_permu);

    cout<<"\n\n\n\n\nROUND 2:";
    vector<int> swap1 = sw2_operation(sw1);

    encrypt_text(swap1);
   
    return 0;
}


