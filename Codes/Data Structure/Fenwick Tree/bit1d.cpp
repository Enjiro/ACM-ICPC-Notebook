class fenwicktree
{
	#define D(x) x&(-x)
	const static int N=100000;
	int tr[N], n;
public:
	fenwicktree(){};
	void build(int _n)
	{
		n=_n;
		memset(tr, 0, sizeof(tr));
	}
	void update(int i, int x)
	{
		for(i++; i<=n; i+=D(i))
			tr[i]+=x;
	}
	int query(int i)
	{
		int ret=0;
		for(i++; i>0; i-=D(i))
			ret+=tr[i];
		return ret;
	}
	int rquery(int l, int r)
	{
		return query(r)-query(l-1);
	}
	void set(int i, int x)
	{
		update(i, -rquery(i, i)+x);
	}
	void rset(int l, int r, int x)
	{
		update(l, x);
		update(r+1, -x);
	}
};