#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long

ll C; // cipher text

int gcd(int a , int b)
{
    if(a==0) return b;
    return gcd(b%a , a);
}

int gcdExtended(int a, int b, int* x, int* y)
{
	if (a == 0)
	{
		*x = 0, *y = 1;
		return b;
	}
	
	int x1, y1;
	int gcd = gcdExtended(b % a, a, &x1, &y1);

	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

int modInverse(int a, int m)
{
	int x, y;
	int g = gcdExtended(a, m, &x, &y);

	int res = (x % m + m) % m;
    return res;	
}

ll square_and_multiply(ll M,  ll exp,  ll n)
{
	ll h;
	ull r;
	int bin[32];
	int i;
	
	r = M;
	i = 0;

	/* Converts exp in Binary */
	while( exp > 0 ){

		if (exp % 2 == 0){
			bin[i] = 0;
		}else{
			bin[i] = 1;
		}

		exp = exp/2;
		i++;

	}

	i--; //t-1

	while(i>0){

		r = (r * r) % n;

		if( bin[--i] == 1 ){
			r = (r * M) % n;
		}
		
	}

	return r;
}

void encrypt(int M, vector<int> pk)
{
    C = square_and_multiply(M,pk[0],pk[1]);
    cout<<"Cipher: "<<C;
}

void decrypt(vector<int> private_k, int n)
{
    ll P = square_and_multiply(C,private_k[0],n);
    cout<<"Original Text: "<<P;
}

int main()
{
    int p,q;
    cout<<"\nEnter Two Prime numbers\n";
    cout<<"P: ";  cin>>p;
    cout<<"q: ";  cin>>q;

    // find n = p * q;
    int n = p * q;

    // find ϕ(n) = (p-1) * (q-1)
    int phi = (p-1) * (q-1);

    // find e--> public key
    int e = 5;
    while (e < phi)
    {
        if (gcd(e, phi)==1)
            break;
        else
            e++;
    }

    int d = modInverse(e, phi);

    vector<int> pk {e,n}; //public key
    vector<int> private_k {d,p,q}; //private key

    //for(auto x: private_k) cout<<x<<" ";

    int M;
    cout<<"\nEnter Message: ";
    cin>>M;

    cout<<"\nENCRYPTION\n";
    encrypt(M,pk);

    cout<<"\n\nDECRYPTION\n";
    decrypt(private_k,n);

    return 0;
}