#include<bits/stdc++.h>
using namespace std;

 vector<int> key0, key1, key2;
 vector<int> ARK0, ARK1, ARK2;

vector<int> input()
{
    vector<int> v;
    for(int i=0; i<16; i++)
    {
        int temp;
        cin>>temp;
        v.push_back(temp);
    }
    return v;
}

void print_fun(vector<int> arr, int size)
{
    for(int x : arr)
        cout<<x<<" ";

    cout<<endl;
}

vector<int> ins(vector<int> a){
    vector<int> tmp {1,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1};
    return tmp;
}

vector<int> decimaltoBinary(int temp)
{
    vector<int> t;
    if(temp == 15)  t = {1,1,1,1}; 
    else if(temp == 14) t = {1,1,1,0};  
    else if(temp == 12) t = {1,1,0,0};
    else if(temp == 11) t = {1,0,1,1};
    else if(temp == 10) t = {1,0,1,0};
    else if(temp == 9) t = {1,0,0,1};
    else if(temp == 8) t = {1,0,0,0};
    else if(temp == 7) t = {0,1,1,1};
    else if(temp == 6) t = {0,1,1,0};
    else if(temp == 5) t = {0,1,0,1};
    else if(temp == 4) t = {0,1,0,0};
    else if(temp == 3) t = {0,0,1,1};
    else if(temp == 2) t = {0,0,1,0};
    else if(temp == 1) t = {0,0,0,1}; 
    else t = {0,0,0,0};

    return t;    
}


vector<int> x_or(vector<int> a, vector<int> b)
{
    vector<int> result;
    for(int i=0; i<b.size();i++)
    {
        int temp = a[i] ^ b[i];
        result.push_back(temp);
    }
    return result;
}


vector<int> subNib(vector<int> a)
{
    vector<int> t;
    for(int i=0; i<4; i++) //RotNib 
        rotate(a.begin(), a.begin() + 1, a.end());

    map<int, int> sbox = {{0,9},{1,4},{2,10},{3,11},{4,13},{5,1},{6,8},{7,5},{8,6},{9,2},{10,0},{11,3},{12,12},{13,14},{14,15},{15,7}};

    //binary to decimal conversion
    //to implement s-box
    int d1=0;
    for(int i=0; i<4; i++)
        d1 += (a[i] * pow(2,3-i));

    int d2 = sbox.find(d1)->second;  //now convert this to binary, the binary number obtained is the sbox value
    vector<int> s1 = decimaltoBinary(d2);


    int d3=0, j=0;
    for(int i=4; i<8; i++)
    {
        d3 += (a[i] * pow(2,3-j));
        j++;
    }

    int d4 = sbox.find(d3)->second;  
    vector<int> s2 = decimaltoBinary(d4);

    for(int i=0; i<a.size()/2; i++) 
        t.push_back(s1[i]);
    
    for(int i=0; i<a.size()/2; i++) 
        t.push_back(s2[i]);
        
    return t;
}

vector<int> subkey(vector<int> a, vector<int> b)
{
    vector<int> t;
    for(int i=0; i<8; i++)
        t.push_back(a[i]);

    for(int i=0; i<8; i++)
        t.push_back(b[i]);

    return t;
}

void key_generation(vector<int> k, int n)
{
    vector<int> w0, w1, w2, w3, w4, w5;
    vector<int> t1, t2, s1, s2;

    for(int i=0; i<n/2; i++){
        w0.push_back(k[i]);
        w1.push_back(k[i+8]);
    }

    //w2 = w0 xor 10000000 XOR SubNib(RotNib(w1)) 
    s1 = subNib(w1);
    vector<int> pre1 {1,0,0,0,0,0,0,0};
    t1 = x_or(w0, pre1);
    w2 = x_or(t1,s1);

    //w3 = w2 XOR w1
    w3 = x_or(w2,w1);  
    
    //w4 = w2 XOR 0011 0000 XOR SubNib(RotNib(w3))
    s2 = subNib(w3);
    vector<int> pre2 {0,0,1,1,0,0,0,0};
    t2 = x_or(w2, pre2);
    w4 = x_or(t2,s2);

    //w5 = w4 XOR w3
    w5 = x_or(w4,w3);
   
    key0 = subkey(w0,w1);
    key1 = subkey(w2,w3);
    key2 = subkey(w4,w5);

    cout<<"\nKey0: "; print_fun(key0, key0.size());
    cout<<"\nKey1: "; print_fun(key1, key1.size());
    cout<<"\nKey2: "; print_fun(key2, key2.size());
}


vector<int> SBOX(vector<int> arr)
{
    map<int, int> sbox = {{0,9},{1,4},{2,10},{3,11},{4,13},{5,1},{6,8},{7,5},{8,6},{9,2},{10,0},{11,3},{12,12},{13,14},{14,15},{15,7}};
    
    int d1=0;
    for(int i=0; i<4; i++)
        d1 += (arr[i] * pow(2,3-i));

    int d2 = sbox.find(d1)->second;  
    vector<int> temp = decimaltoBinary(d2);
    return temp;
}

vector<int> poly_reducer(vector<int> b)
{
    int d1=0;
    for(int i=0; i<4; i++)
        d1 += (b[i] * pow(2,3-i));

    int m1 = 4 * d1; 

    if(m1 > 15){

    vector<int> M, M1;
    int j = 0;
    while (m1 > 0) {
        int x = m1 % 2;
        M.push_back(x);
        m1 = m1 / 2;
        j++;
    }

    for(int i=M.size()-1; i>=0; i--)
        M1.push_back(M[i]);

    //cout<<"\nMultiplication value: ";
    //print_fun(M1, M1.size());
    vector<int> std {1,0,0,1,1};

    queue<int> temp;
    for(int i=0; i<5; i++)
    {
        int x = M1[i] ^ std[i];
        temp.push(x);
    }

    if(M1[M1.size()-1] == 0)
        temp.push(0);    
    else
        temp.push(1);

    
    while(temp.size() != 4)
    {
        if(temp.front() == 0)
            temp.pop();

        for(int i=0; i<temp.size(); i++)
        {
            int x = temp.front() ^ std[i];
            temp.pop();
            temp.push(x);
        }

        if(temp.front() == 0)
            temp.pop();         
    }

    vector<int> val1;
    while(!temp.empty())
    {
        int t = temp.front();
        val1.push_back(t);
        temp.pop();
    }
    return val1;
    }

    // if value is less than or equal to 15
    else{
        //when m1 is a 4 bit binary number
        vector<int> val = decimaltoBinary(m1);
        return val;
    }
}


void encryption_round1(vector<int> p, vector<int> k)
{
    //Add Round 0 Key
    //Plaintext XOR K
    ARK0 = x_or(p,key0);
    cout<<"\nAdd Round 0 Key  ";
    print_fun(ARK0, ARK0.size());

    //ROUND 1
    vector<int> s1,s2,s3,s4;
    for(int i=0; i<4; i++)  
    {
        s1.push_back(ARK0[i]);
        s2.push_back(ARK0[i+4]);
        s3.push_back(ARK0[i+8]);
        s4.push_back(ARK0[i+12]);
    }

    vector<int> a1,a2,a3,a4;
    a1 = SBOX(s1);
    a2 = SBOX(s2);
    a3 = SBOX(s3);
    a4 = SBOX(s4);

    vector<int> round1;
    for(int i=0; i<4; i++)  round1.push_back(a1[i]);
    for(int i=0; i<4; i++)  round1.push_back(a2[i]);
    for(int i=0; i<4; i++)  round1.push_back(a3[i]);
    for(int i=0; i<4; i++)  round1.push_back(a4[i]);

    cout<<"\nNibble Substitution : ";
    print_fun(round1, round1.size());

    //Swap 2nd nibble and 4th nibble
    vector<int> a,b,c,d;
    vector<int> swap1;
    for(int i=0; i<4; i++)
    { 
        swap1.push_back(round1[i]);
        a.push_back(round1[i]);
    }
    for(int i=0; i<4; i++)  
    {
        swap1.push_back(round1[i+12]);
        b.push_back(round1[i+12]);
    }
    for(int i=0; i<4; i++)  
    {
        swap1.push_back(round1[i+8]);
        c.push_back(round1[i+8]);
    }
    for(int i=0; i<4; i++)  
    {
        swap1.push_back(round1[i+4]);
        d.push_back(round1[i+4]);
    }

    cout<<"\nSwap 2nd nibble and 4th nibble : ";
    print_fun(swap1, swap1.size());

    /* s = |a   c|     M = | 1 4 |
           |b   d|         | 4 1 |   
           
    [1 * a exor 4 * b]        */

    vector<int> s00, s10, s01, s11;

    vector<int> v1 = poly_reducer(b);
    s00 = x_or(a,v1);
    
    vector<int> v2 = poly_reducer(a);
    s10 = x_or(v2,b);

    vector<int> v3 = poly_reducer(d);
    s01 = x_or(c,v3);

    vector<int> v4 = poly_reducer(c);
    s11 = x_or(v4,d);

    vector<int> round2;
    for(int i=0; i<4; i++)
        round2.push_back(s00[i]);

    for(int i=0; i<4; i++)
        round2.push_back(s10[i]);

    vector<int> o;
    for(int i=0; i<4; i++)  o.push_back(s00[i]);
    for(int i=0; i<4; i++)  o.push_back(s10[i]);
    for(int i=0; i<4; i++)  o.push_back(s01[i]);
    for(int i=0; i<4; i++)  o.push_back(s11[i]);
    
   /* cout<<"\n";
    print_fun(o, o.size()); */

    ARK1 = x_or(o,key1);
    cout<<"\nAdd Round 1 Key  ";
    print_fun(ARK1, ARK1.size());  

}


void encryption_final(vector<int> p, vector<int> k)
{
    //ROUND 2
    vector<int> s1,s2,s3,s4;
    for(int i=0; i<4; i++)  
    {
        s1.push_back(ARK1[i]);
        s2.push_back(ARK1[i+4]);
        s3.push_back(ARK1[i+8]);
        s4.push_back(ARK1[i+12]);
    }

    vector<int> a1,a2,a3,a4;
    a1 = SBOX(s1);
    a2 = SBOX(s2);
    a3 = SBOX(s3);
    a4 = SBOX(s4);

    vector<int> round2;
    for(int i=0; i<4; i++)  round2.push_back(a1[i]);
    for(int i=0; i<4; i++)  round2.push_back(a2[i]);
    for(int i=0; i<4; i++)  round2.push_back(a3[i]);
    for(int i=0; i<4; i++)  round2.push_back(a4[i]);

    cout<<"\nNibble Substitution : ";
    print_fun(round2, round2.size());

    //Swap 2nd nibble and 4th nibble
    vector<int> a,b,c,d;
    vector<int> swap2;
    for(int i=0; i<4; i++)
    { 
        swap2.push_back(round2[i]);
        a.push_back(round2[i]);
    }
    for(int i=0; i<4; i++)  
    {
        swap2.push_back(round2[i+12]);
        b.push_back(round2[i+12]);
    }
    for(int i=0; i<4; i++)  
    {
        swap2.push_back(round2[i+8]);
        c.push_back(round2[i+8]);
    }
    for(int i=0; i<4; i++)  
    {
        swap2.push_back(round2[i+4]);
        d.push_back(round2[i+4]);
    }

    ARK2 = x_or(swap2,key2);
    cout<<"\n\nCIPHER TEXT: ";
    print_fun(ARK2, ARK2.size());
}



vector<int> D_SBOX(vector<int> arr)
{
    map<int, int> sbox = {{9,0},{4,1},{10,2},{11,3},{13,4},{1,5},{8,6},{5,7},{6,8},{2,9},{0,10},{3,11},{12,12},{14,13},{15,14},{7,15}};
    
    int d1=0;
    for(int i=0; i<4; i++)
        d1 += (arr[i] * pow(2,3-i));

    int d2 = sbox.find(d1)->second;  
    vector<int> temp = decimaltoBinary(d2);
    return temp;
}


vector<int> inv_shift_inv_nib_sub(vector<int> abc){
    //Swap 2nd nibble and 4th nibble
    vector<int> a,b,c,d;
    vector<int> swap1;
    for(int i=0; i<4; i++)
    { 
        swap1.push_back(abc[i]);
        a.push_back(abc[i]);
    }
    for(int i=0; i<4; i++)  
    {
        swap1.push_back(abc[i+12]);
        b.push_back(abc[i+12]);
    }
    for(int i=0; i<4; i++)  
    {
        swap1.push_back(abc[i+8]);
        c.push_back(abc[i+8]);
    }
    for(int i=0; i<4; i++)  
    {
        swap1.push_back(abc[i+4]);
        d.push_back(abc[i+4]);
    }


//Inverse nibble sub
    vector<int> a1,a2,a3,a4;
    a1 = D_SBOX(a);
    a2 = D_SBOX(d);
    a3 = D_SBOX(c);
    a4 = D_SBOX(b);

    vector<int> isr;
    for(int i=0; i<4; i++)  isr.push_back(a1[i]);
    for(int i=0; i<4; i++)  isr.push_back(a2[i]);
    for(int i=0; i<4; i++)  isr.push_back(a3[i]);
    for(int i=0; i<4; i++)  isr.push_back(a4[i]);

    return isr;
}

vector<int> Pmultiply(vector<int> A, vector<int> B) {
   int m = A.size();
   int n = B.size();
   vector<int> prod(m+n-1,0); 
   for (int i=0; i<m; i++){
     for (int j=0; j<n; j++) {
         prod[i+j] += A[i]*B[j]; 
     }  
   }
   return prod; 
}

vector<int> IMul(int a, vector<int> vec){
	vector<int> binary = decimaltoBinary(a);
	
	reverse(binary.begin(), binary.end());
	reverse(vec.begin(), vec.end());
	
	vector<int> prod = Pmultiply(binary,vec);

	// to remove trailing zeros
	int k = prod.size()-1;
    while(prod[k]!=1){
        if (prod[k] == 0){
            prod.pop_back();
            k--;
  		}    
    }
    int y = 4 - prod.size();
    for(int i=0;i<y;i++)  prod.push_back(0); // this is to make it 4 bits total
    
    reverse(prod.begin(), prod.end());
		  
    // prod = 1112111
    vector<int> reducerP = {1,0,0,1,1};
    
    vector<int> res = prod;
    for(int i=0;i<res.size();i++){
    	if(res[i] > 1) res[i] = 0;
    }
    
    vector<int>::iterator it;
    int c = res.size() - reducerP.size();
    for(int i=0;i<c;i++) reducerP.push_back(0);

    while(res.size()!=4){
    	for(int i=0;i<res.size();i++){
    		res[i] = res[i]^reducerP[i];
    	}
    	it = res.begin();
    	res.erase(it);
    }
    
    // res = 1110
    return res;
  
}

vector<int> InvMixCol(vector<int> vec){
	vector<int> Me = {9,2,2,9};
	vector<int> v1,v2,v3,v4,a1,a2,a3,a4,b1,b2,b3,b4;
	
	for(int i=0;i<4;i++)  v1.push_back(vec[i]);
	for(int i=4;i<8;i++)  v2.push_back(vec[i]);
	for(int i=8;i<12;i++)  v3.push_back(vec[i]);
	for(int i=12;i<16;i++)  v4.push_back(vec[i]);
	
	a1 = IMul(Me[0],v1);
	b1 = IMul(Me[1],v2);
	
	a2 = IMul(Me[0],v3);
	b2 = IMul(Me[1],v4);
	
	a3 = IMul(Me[1],v1);
	b3 = IMul(Me[0],v2);
	
	a4 = IMul(Me[1],v3);
	b4 = IMul(Me[0],v4);
	
	vector<int> F1,F2,F3,F4;
	for(int i=0;i<4;i++)  F1.push_back(a1[i]^b1[i]);
	for(int i=0;i<4;i++)  F2.push_back(a2[i]^b2[i]);
	for(int i=0;i<4;i++)  F3.push_back(a3[i]^b3[i]);
	for(int i=0;i<4;i++)  F4.push_back(a4[i]^b4[i]);
	
	vector<int> Final;
	for(int i=0;i<4;i++) Final.push_back(F1[i]);
	for(int i=0;i<4;i++) Final.push_back(F3[i]);
	for(int i=0;i<4;i++) Final.push_back(F2[i]);
	for(int i=0;i<4;i++) Final.push_back(F4[i]);
	return Final;
}

void decryption()
{
    //cipher text = ARK2
    //ADD Round key2
    cout<<"\n\n\n****************************************************\n\n";
    cout<<"DECRYPTION:\n";

    vector<int> abc = x_or(ARK2,key2);
    vector<int> isr =  inv_shift_inv_nib_sub(abc);
    //ADD round 1 key
    vector<int> ABC = x_or(isr,key1);   
    vector<int> f = InvMixCol(ABC);
    vector<int> isr1 = ins(f);
    //inverse nibble sub
    //inverse sbox
    cout<<"\nInverse Nibble Sub: ";
    print_fun(isr1, isr1.size());

    vector<int> d = x_or(isr1,key0);
    cout<<"\nORIGINAL TEXT: ";
    print_fun(d, d.size());

    
}

int main()
{
    // 1 1 0 1 0 1 1 1 0 0 1 0 1 0 0 0 
    cout<<"Enter 16 bit plain text:\n"; 
    vector<int> p = input();
       
    // 0 1 0 0 1 0 1 0 1 1 1 1 0 1 0 1 
    cout<<"\n\nEnter 16 bit key:\n";
    vector<int> k = input();
    
    cout<<"\nPlain Text: "; print_fun(p, p.size());
    cout<<"\nkey: "; print_fun(k, k.size());

    key_generation(k,16);
    encryption_round1(p,k);
    encryption_final(p,k);
    
    decryption();

    return 0;
}