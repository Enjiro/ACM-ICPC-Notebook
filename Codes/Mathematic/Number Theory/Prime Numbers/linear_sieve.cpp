//prime(x):(lp[x]==x)
const int MN=1e+6;
long long lp[MN+1];
vector<long long>pr;

void sieve()
{
	for(long long i=2; i<=MN; i++)
	{
		if(lp[i]==0)
		{
			lp[i]=i;
			pr.push_back(i);
		}
		for(long long j=0; j<pr.size() && pr[j]<=lp[i] && i*pr[j]<=MN; j++)
			lp[i*pr[j]]=pr[j];
	}
}