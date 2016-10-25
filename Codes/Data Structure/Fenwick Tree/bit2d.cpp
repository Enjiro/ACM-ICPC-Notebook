class fenwicktree
{
	#define D(x) x&(-x)
	const static int N=1000;
	int tr[N][N], n, m;
public:
	fenwicktree(){};
	void build(int _n, int _m)
	{
		n=_n, m=_m;
		memset(tr, 0, sizeof(tr));
	}
	void update(int r, int c, int x)
	{
		for(int i=r+1; i<=n; i+=D(i))
			for(int j=c+1; j<=m; j+=D(j))
				tr[i][j]+=x;
	}
	int query(int r, int c)
	{
		int ret=0;
		for(int i=r+1; i>0; i-=D(i))
			for(int j=c+1; j>0; j-=D(j))
				ret+=tr[i][j];
		return ret;
	}
	int rquery(int r1, int c1, int r2, int c2)
	{
		if((r1>r2 && c1>c2) || (r1==r2 && c1>c2) || (r1>r2 && c1==c2))
		{
			swap(r1, r2);
			swap(c1, c2);
		}
		else if(r1<r2 && c1>c2)
		{
			swap(c1,c2);
		}
		else if(r1>r2 && c1<c2)
		{
			swap(r1,r2);
		}
		return query(r2, c2)-query(r1-1, c2)-query(r2, c1-1)+query(r1-1, c1-1);
	}
	void set(int r, int c, int x)
	{
		update(r, c, -rquery(r, c, r, c)+x);
	}
};