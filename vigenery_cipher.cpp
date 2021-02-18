//implementation of vegenary-cipher
#include<bits/stdc++.h>
using namespace std;

vector<char> alpha = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
                    'n','o','p','q','r','s','t','u','v','w','x','y','z'};

 void encrypt(string str, vector<int>& k)
{
     for(int i=0;i<str.length();i++)
    {
        int index = str[i] + k[i];
        index = index % 97;

        if(index > 25)
        {
            index = index%26;
        }

        cout<<alpha[index];
    }
}

int main()
{ 
    string s;
    cout<<"\nEnter message: ";
    getline(cin,s);
  
    cout<<"Enter cipher keys: ";
    vector<int> k;
    for(int i=0; i<s.length(); i++)
    {
        int x;
        cin>>x;
        k.push_back(x);
    }

    cout<<"Printing the Encrypted message: ";
    encrypt(s,k);

    return 0;
}