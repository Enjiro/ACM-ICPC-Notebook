//call sieve() before isPrime(x)
//define k=50 as trivial limit
bool isPrime(ll x)
{
	if(x==1)
		return false;
	if(x==2)
		return true;
	if(x%2==0)
		return false;
	for(int i=0; i<k && x>pr[i]; i++)
		if(x%pr[i]==0)
			return false;
	if(pr[k-1]*pr[k-1]>=x)
		return true;
	//return only millerRabin(x) for fast process
	//not accurate for all x
	return millerRabin(x)?bpsw(x):false;
}