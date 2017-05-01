typedef long long ll;
typedef vector<vector<ll> > matrix;
const ll MOD=303700049;
int n, t;
ll k;
ll val[101];

ll modmul(ll a, ll b)
{
	return ((a%MOD)*(b%MOD))%MOD;
}

ll modsum(ll a, ll b)
{
	return ((a%MOD)+(b%MOD))%MOD;
}

matrix basem;
matrix mat_mul(matrix A, matrix B)
{
	int t=A.size();
	matrix ret=basem;
	for(int i=0; i<t; i++)
	{
		for(int j=0; j<t; j++)
		{
			for(int k=0; k<t; k++)
			{
				ret[i][j]=(ret[i][j]+A[i][k]*B[k][j]);
			}
			ret[i][j]%=MOD;
		}
	}
	return ret;
}

matrix mat_pow(matrix &A, ll k)
{
	if(k==1)
		return A;
	if(k&1)
		return mat_mul(A, mat_pow(A,k-1));
	matrix ret=mat_pow(A, k>>1);
	return mat_mul(ret, ret);
}

//o build pode variar, sendo ele a base do fibonacci
matrix build()
{
	matrix ret(t, vector<ll>(t));
	for(int i=0; i<n; i++)
		ret[0][i]=i+1;
	for(int i=1; i<n; i++)
		for(int j=0; j<n; j++)
			ret[i][j]=(j+1==i);
	for(int i=0; i<n; i++)
		ret[t-1][i]=i+1;
	ret[t-1][t-1]=1;
	return ret;
}

pair<ll,ll>calc(ll k)
{
	if(n>=k)
		return mp(val[k-1], 0);
	matrix base=build();
	matrix fib=mat_pow(base, k-n);

	ll ret=0;
	reverse(val, val+n);
	for(int i=0; i<n; i++)
		ret=modsum(ret, modmul(fib[0][i], val[i]));

	ll sum=0;
	for(int i=0; i<n; i++)
		sum=modsum(sum, modmul(fib[n][i], val[i]));
	return mp(ret, sum);
}

void solve()
{
	//First = f(n-x), Second = somatoaria de f(0) ate f(n-x)
	pair<ll,ll>ans=calc(k);
	if(k>n)
	{
		for(int i=0; i<n; i++)
		{
			ans.S=ans.S+val[i];
			if(ans.S>MOD)
				ans.S%=MOD;
		}
	}
	else
	{
		for(int i=0; i<k; i++)
		{
			ans.S=ans.S+val[i];
			if(ans.S>MOD)
				ans.S%=MOD;
		}
	}
	printf("%lld %lld\n", ans.F, ans.S);
}

int main()
{
	while(scanf("%d %lld", &n, &k)!=EOF)
	{
		t=n+1;
		basem.clear();
		basem.resize(t, vector<ll>(t));
		//val[i] = valores iniciais conhecidos da recorrencia
		for(int i=0; i<n; i++)
		{
			scanf("%lld", &val[i]);
		}
		solve();
	}
	return 0;
}