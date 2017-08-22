//after sieve
ll phi(ll x)
{
	ll ret=x;
	while(x>1)
	{
		ll y=lp[x];
		while(x%y==0)
			x/=y;
		ret-=ret/y;
	}
	if(x>1)
		ret-=ret/x;
	return ret;
}