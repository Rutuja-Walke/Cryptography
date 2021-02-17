//implementation of caesar-cipher
#include<bits/stdc++.h>
using namespace std;

vector<char> alpha = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
                    'n','o','p','q','r','s','t','u','v','w','x','y','z'};

 void encrypt(string str, int key)
{
     for(int i=0;i<str.length();i++)
    {
        int index = str[i] + key;
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

    int k;
    cout<<"Enter cipher key: ";
    cin>>k;

    cout<<"Printing the Encrypted message: ";
    encrypt(s,k);
    return 0;
}