//implementation of caesar-cipher
#include<bits/stdc++.h>
using namespace std;

vector<char> alpha = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
                    'n','o','p','q','r','s','t','u','v','w','x','y','z'};

vector<char> uaplha = {'A','B','C','D','E','F','G','H','I','K','L','M','N','O','P','Q','R',
                        'S','T','U','V','W','X','Y','Z'};

 void encrypt(string str, int key)
{
     for(int i=0;i<str.length();i++)
    {
        if(islower(str[i]))
        {
            int index = str[i] + key;
            index = index % 97;

            if(index > 25)
            {
                index = index % 26;
            }

            cout<<alpha[index];
        }

        else
        {
            int index = str[i] + key;
            index = index % 65;

               if(index > 25)
            {
                index = index%26;
            }

            cout<<uaplha[index];            
        }
    }
    
}

int main()
{ 
    string s;
    cout<<"\nEnter message: ";
    getline(cin,s);

    int k;
    cout<<"Enter cipher key: ";
    cin>>k;

    cout<<"Printing the Encrypted message: ";
    encrypt(s,k);
    return 0;
}
