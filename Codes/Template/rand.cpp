inline ll bigRand(ll mod)//[0, mod]
{
	mod--;
	ll ret=rand()*rand();
	return (abs(ret<<(rand()%32))%mod)+(rand()%2);
}

inline int smallRand(int mod)//[0, mod]
{
	mod--;
	int ret=rand()*rand();
	return (abs(ret<<(rand()%20))%mod)+(rand()%2);
}
