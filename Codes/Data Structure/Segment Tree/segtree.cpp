class segtree
{
	const static int N=100000;
	int tr[4*N], lazy[4*N];
public:
	segtree(){};
	void clear()
	{
		memset(tr, 0, sizeof(tr));
		memset(lazy, 0, sizeof(lazy));
	}
	void build(int no, int l, int r, vector<int>&data)
	{
		if(l==r)
		{
			tr[no]=data[l];
			return;
		}
		int nxt=no*2;
		int mid=(l+r)/2;
		build(nxt, l, mid, data);
		build(nxt+1, mid+1, r, data);
		tr[no]=tr[nxt]+tr[nxt+1];
	}
	void propagate(int no, int l, int r)
	{
		if(!lazy[no])
			return;
		
		tr[no]+=(r-l+1)*lazy[no];
		if(l!=r)
		{
			int nxt=no*2;
			lazy[nxt]+=lazy[no];
			lazy[nxt+1]+=lazy[no];
		}
		lazy[no]=0;
	}
	void update(int no, int l, int r, int i, int j, int x)
	{
		propagate(no, l, r);
		if(l>j || r<i)
			return;
		if(l>=i && r<=j)
		{
			lazy[no]=x;
			propagate(no, l, r);
			return;
		}
		int nxt=no*2;
		int mid=(l+r)/2;
		update(nxt, l, mid, i, j, x);
		update(nxt+1, mid+1, r, i, j, x);
		tr[no]=tr[nxt]+tr[nxt+1];
	}
	int query(int no, int l, int r, int i, int j)
	{
		propagate(no, l, r);
		if(l>j || r<i)
			return 0;
		if(l>=i && r<=j)
			return tr[no];
		int nxt=no*2;
		int mid=(l+r)/2;
		int ql=query(nxt, l, mid, i, j);
		int qr=query(nxt+1, mid+1, r, i, j);
		return (ql+qr);
	}
};
