//set MOD
const ll MOD=1e+9;
class matrix
{
	const static int N=2;
public:
	ll v[N][N];
	matrix(){};
	matrix(ll _v[])
	{
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				v[i][j]=(i+1==j);
		for(int i=0; i<N; i++)
			v[N-1][i]=_v[i];
	}
	matrix operator *(const matrix &foo)
	{
		matrix ret;
		SET(ret.v, 0);
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
				for(int k=0; k<N; k++)
				{
					ret.v[i][j]+=(v[i][k]*foo.v[k][j]);
				}
				ret.v[i][j]%=MOD;
			}
		}
		return ret;
	}
	matrix pow(matrix b, ll m)
	{
		if(m==1)
			return b;
		if(m&1)
			return b*pow(b, m-1);
		matrix ret=pow(b, m>>1);
		return ret*ret;
	}
};

//b[i] = f(1), f(2), f(i+1), f(i+2), ..., f(n)
ll b[2]={1, 1};
ll fib(ll x)
{
	if(x<=2)
		return b[x-1];
	matrix aux=matrix().pow(matrix(b), x-1);
	ll ret=0;
	for(int i=0; i<2; i++)
		ret=(ret+(b[i]*aux.v[0][i])%MOD)%MOD;
	return ret;
}