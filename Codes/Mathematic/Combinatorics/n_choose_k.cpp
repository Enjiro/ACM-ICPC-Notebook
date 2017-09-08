int C (int n, int k)
{
	int res = 1;
	for (int i=n-k+1; i<=n; ++i)
		res *= i;
	for (int i=2; i<=k; ++i)
		res /= i;
	return res;
}