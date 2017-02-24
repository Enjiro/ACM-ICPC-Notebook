//millerRabin(n) returns if n is prime
//not accurate for all n 
#define gcd(x, y) __gcd(x, y)
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