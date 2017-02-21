//call sieve() before isPrime(x)
//isPrime(x) returns if x is prime or not
//not always corret for all x

#define gcd(x, y) __gcd(x, y)
const int MN=1000;
int lp[MN+1];
vector<ll>pr;
int k=50; //trivial limit for prime test
void sieve()
{
	for(int i=2; i<=MN; i++)
	{
		if(lp[i]==0)
		{
			lp[i]=i;
			pr.pb((ll)i);
			if(pr.size()==k)
				return;
		}
		for(int j=0; j<pr.size() && pr[j]<=lp[i] && i*pr[j]<=MN; j++)
			lp[ i*pr[j] ]=pr[j];
	}
}

ll powmod(ll a, ll b, ll m)
{
	ll ret=1;
	while(b)
	{
		if(b&1)
			ret=(ret*a)%m, --b;
		else
			a=(a*a)%m, b>>=1;
	}
	return ret;
}

bool millerRabin(ll n)
{
	ll b=2;
	for(ll g; (g=gcd(n, b))!=1; b++)
		if(n>g)
			return false;
	ll p=0, q=n-1;
	while((q&1)==0)
		p++, q>>=1;
	ll rem=powmod(b, q, n);
	if(rem==1 || rem==n-1)
		return true;
	for(ll i=1; i<p; i++)
	{
		rem=(rem*rem)%n;
		if(rem==n-1)
			return true;
	}
	return false;
}

bool isPrime(ll x)
{
	if(n==1)
		return false;
	if(n==2)
		return true;
	if(n%2==0)
		return false;
	for(int i=0; i<k && x>pr[i]; i++)
		if(x%pr[i]==0)
			return false;
	if(pr[k-1]*pr[k-1]>=x)
		return true;
	return millerRabin(x);
}