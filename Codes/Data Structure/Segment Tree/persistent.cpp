class persistent_segtree
{
	const static int N=100000;
	int n;
	int tr[N];
	int root[N], L[N], R[N];
	int cnt, id;
public:
	persistent_segtree(){};
	void set(int _n)
	{
		memset(tr, 0, sizeof(tr));
		memset(root, 0, sizeof(root));
		memset(L, 0, sizeof(L));
		memset(R, 0, sizeof(R));
		id=0;
		cnt=1;
		n=_n;
	}
	void build(int no, int l, int r, vector<int>&data)
	{
		if(l==r)
		{
			tr[no]=data[l];
			return;
		}
		int mid=(l+r)/2;
		L[no]=cnt++;
		R[no]=cnt++;
		build(L[no], l, mid, data);
		build(R[no], mid+1, r, data);
		tr[no]=tr[ L[no] ]+tr[ R[no] ];
	}
	int update(int no, int l, int r, int i, int x)
	{
		int newno=cnt++;
		tr[newno]=tr[no];
		L[newno]=L[no];
		R[newno]=R[no];
		if(l==r)
		{
			tr[newno]=x;
			return newno;
		}
		int mid=(l+r)/2;
		if(i<=mid)
			L[newno]=update(L[newno], l, mid, i, x);
		else
			R[newno]=update(R[newno], mid+1, r, i, x);
		tr[newno]=tr[ L[newno] ]+tr[ R[newno] ];
		return newno;
	}
	int query(int no, int l, int r, int i, int j)
	{
		if(r<i || l>j)
			return 0;
		if(l>=i && r<=j)
			return tr[no];
		int mid=(l+r)/2;
		int ql=query(L[no], l, mid, i, j);
		int qr=query(R[no], mid+1, r, i, j);
		return ql+qr;
	}
	//update the i-th value to x.
	void update(int i, int x)
	{
		root[id+1]=update(root[id], 0, n-1, i, x);
	}
	//returns sum(l, r) after the k-th update.
	int query(int l, int r, int k)
	{
		return query(root[k], 0, n-1, l, r);
	}
};