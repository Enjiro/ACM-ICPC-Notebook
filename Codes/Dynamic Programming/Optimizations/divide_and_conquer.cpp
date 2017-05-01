typedef long long ll;
const int MN=1e+4+35;
const int MN2=535;
int p, a;
ll data[MN];
inline ll getValue(int l, int r)
{
	return (r-l+1)*(data[r]-data[l-1]);
}
ll dp[MN2][MN];
inline void solve(int k, int l, int r, int L, int R)
{
	if(l>r)
		return;
	int m=(l+r)/2;
	int s=L;
	dp[k][m]=LINF;
	for(int i=max(m, L); i<=R; i++)
	{
		if(dp[k][m]>dp[k-1][i+1]+getValue(m+1, i+1))
		{
			dp[k][m]=dp[k-1][i+1]+getValue(m+1, i+1);
			s=i;
		}
	}
	solve(k, l, m-1, L, s);
	solve(k, m+1, r, s, R);
}
int main()
{
	scanf("%d %d", &p, &a);
	for(int i=1; i<=p; i++)
	{
		ll x;
		scanf("%lld", &x);
		data[i]=data[i-1]+x;
	}
	for(int i=0; i<=p; i++)
		dp[0][i]=LINF;
	for(int i=0; i<=a; i++)
		dp[i][p]=0;
	for(int i=1; i<=a; i++)
		solve(i, 0, p-1, 0, p-1);
	printf("%lld\n", dp[a][0]);
}