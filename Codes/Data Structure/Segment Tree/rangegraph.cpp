/*
call build(1, 0, n-1, 0) & build(1, 0, n-1, 1)
to build base graph on tree

update(1, 0, n-1, l, r, x, 0):
add vertex [x,x]->[l, r]

update(1, 0, n-1, l, r, x, 1):
add vertex [l,r]->[x,x]
*/
class segtree
{
	const static int N=1e+5+35;
public:
	vector<pii>data[8*N];
	int idx[4*N][2], id;
	segtree(){};
	void set(int n)
	{
		id=n;
		for(int i=0; i<8*n; i++)
			data[i].clear();
	}
	inline void addEdge(int u, int v, int w)
	{
		data[u].pb({v, w});
	}
	inline void build(int no, int l, int r, int t)
	{
		idx[no][t]=id++;
		if(l==r)
		{
			if(!t)
				addEdge(idx[no][t], l, 0);
			else
				addEdge(l, idx[no][t], 0);
			return;
		}
		int nxt=no<<1;
		int mid=(l+r)>>1;
		build(nxt, l, mid, t);
		build(nxt+1, mid+1, r, t);
		if(!t)
		{
			addEdge(idx[no][t], idx[nxt][t], 0);
			addEdge(idx[no][t], idx[nxt+1][t], 0);
		}
		else
		{
			addEdge(idx[nxt][t], idx[no][t], 0);
			addEdge(idx[nxt+1][t], idx[no][t], 0);
		}
	}
	inline void update(int no, int l, int r, int i, int j, int u, int w, int t)
	{
		if(l>j || r<i)
			return;
		if(l>=i && r<=j)
		{
			if(!t)
				addEdge(u, idx[no][t], w);
			else
				addEdge(idx[no][t], u, w);
			return;
		}
		int nxt=no<<1;
		int mid=(l+r)>>1;
		update(nxt, l, mid, i, j, u, w, t);
		update(nxt+1, mid+1, r, i, j, u, w, t);
	}
};