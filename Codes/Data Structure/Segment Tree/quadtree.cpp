class quadtree
{
	//needs to be NxN
	const static int N=100000;
	int tr[16*N];
public:
	quadtree(){};
	void build(int node, int l1, int r1, int l2, int r2, vector< vector<int> >data)
	{
		if(l1==l2 && r1==r2)
		{
			tr[node]=data[l1][r1];
			return;
		}
		int nxt=node*4;
		int midl=(l1+l2)/2;
		int midr=(r1+r2)/2;

		build(nxt-2, l1, r1, midl, midr, data);
		build(nxt-1, midl+1, r1, l2, midr, data);
		build(nxt, l1, midr+1, midl, r2, data);
		build(nxt+1, midl+1, midr+1, l2, r2, data);

		tr[node]=tr[nxt-2]+tr[nxt-1]+tr[nxt]+tr[nxt+1];
	}
	void update(int node, int l1, int r1, int l2, int r2, int i, int j, int x)
	{
		if(l1>l2 || r1>r2)
			return;
		if(i>l2 || j>r2 || i<l1 || j<r1)
			return;
		if(i==l1 && i==l2 && j==r1 && j==r2)
		{
			tr[node]=x;
			return;
		}
		int nxt=node*4;
		int midl=(l1+l2)/2;
		int midr=(r1+r2)/2;

		update(nxt-2, l1, r1, midl, midr, i, j, x);
		update(nxt-1, midl+1, r1, l2, midr, i, j, x);
		update(nxt, l1, midr+1, midl, r2, i, j, x);
		update(nxt+1, midl+1, midr+1, l2, r2, i, j, x);

		tr[node]=tr[nxt-2]+tr[nxt-1]+tr[nxt]+tr[nxt+1];
	}
	int query(int node, int l1, int r1, int l2, int r2, int i1, int j1, int i2, int j2)
	{
		if(i1>l2 || j1>r2 || i2<l1 || j2<r1 || i1>i2 || j1>j2)
			return 0;
		if(i1<=l1 && j1<=r1 && l2<=i2 && r2<=j2)
			return tr[node];
		int nxt=node*4;
		int midl=(l1+l2)/2;
		int midr=(r1+r2)/2;

		int q1=query(nxt-2, l1, r1, midl, midr, i1, j1, i2, j2);
		int q2=query(nxt-1, midl+1, r1, l2, midr, i1, j1, i2, j2);
		int q3=query(nxt, l1, midr+1, midl, r2, i1, j1, i2, j2);
		int q4=query(nxt+1, midl+1, midr+1, l2, r2, i1, j2, i2, j2);
	}
};