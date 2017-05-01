typedef long long ll;
const int MN=6005;
ll v[MN];
ll dp[MN][MN];
ll c[MN][MN];

ll sum[MN];
ll multisum[MN];

void solve(int k, int l, int r, int L, int R)
{
	if(l>r)
		return;
	int m=(l+r)/2;
	int s=-1;
	dp[k][m]=LINF;
	for(int i=max(m, L); i<=R; i++)
	{
		if(dp[k][m]>dp[k-1][i+1]+c[m][i])
		{
			dp[k][m]=dp[k-1][i+1]+c[m][i];
			s=i;
		}
	}
	solve(k, l, m-1, L, s);
	solve(k, m+1, r, s, R);
}

ll dist(int l, int r, int mid)
{
	ll s1=sum[mid]-sum[l];
	ll p1=multisum[mid]-multisum[l];
	ll s2=sum[r+1]-sum[mid+1];
	ll p2=multisum[r+1]-multisum[mid+1];
	return (s1*mid-p1)+(p2-s2*mid);
}

int main()
{
	int n;
	ll b, k;
	scanf("%d %lld %lld", &n, &b, &k);
	for(int i=0; i<n; i++)
	{
		scanf("%lld", &v[i]);
		sum[i+1]=sum[i]+v[i];
		multisum[i+1]=multisum[i]+v[i]*1LL*i;
	}

	for(int i=0; i<n; i++)
	{
		int mid=i;
		ll tot=0;
		ll smid=v[i];
		for(int j=i; j<n; j++)
		{
			tot+=v[j];
			while(smid+smid<tot)
				smid+=v[++mid];
			c[i][j]=k*dist(i, j, mid);
		}
	}
	for(int i=0; i<=n; i++)
		dp[0][i]=LINF;
	for(int i=0; i<=k; i++)
		dp[i][n]=0;

	for(int i=1; i<=n; i++)
	{
		solve(i, 0, n-1, 0, n-1);
		i>1?printf(" "):NULL;
		printf("%lld", i*b+dp[i][0]);
	}
	printf("\n");

	return 0;
}