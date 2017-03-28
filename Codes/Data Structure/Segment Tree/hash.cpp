const int NC=1e+5;
ull aux[NC];
void precalc(ull k)
{
	aux[0]=1LL;
	for(int i=1; i<NC; i++)
		aux[i]=aux[i-1]*k;
}

class node
{
public:
	ull v;
	int s;
	node(){};
	node(ull _v, int _s)
	{
		v=_v; s=_s;
	}
	node operator +(const node &foo) const
	{
		return node(v+(foo.v*aux[s]), s+foo.s);
	}
};

class segtree
{
	const static int N=1e+5+35;
	node tr[4*N];
public:
	segtree(){};
	void update(int no, int l, int r, int i, int j, node x)
	{
		if(l>j || r<i)
			return;
		if(l>=i && r<=j)
		{
			tr[no]=x;
			return;
		}
		int mid=(l+r)>>1;
		int nxt=no<<1;
		update(nxt, l, mid, i, j, x);
		update(nxt+1, mid+1, r, i, j, x);
		tr[no]=tr[nxt]+tr[nxt+1];
	}
	node query(int no, int l, int r, int i, int j)
	{
		if(l>j || r<i)
			return node(0LL, 0);
		if(l>=i && r<=j)
			return tr[no];
		int mid=(l+r)>>1;
		int nxt=no<<1;
		node ql=query(nxt, l, mid, i, j);
		node qr=query(nxt+1, mid+1, r, i, j);
		return ql+qr;
	}
};