class mergesort_segtree
{
	const static int N=100000;
	vector<int>tr[4*N];
public:
	mergesort_segtree(){};
	void build(int no, int l, int r, vector<int>&data)
	{
		if(l==r)
		{
			tr[no].push_back(data[l]);
			return;
		}
		int nxt=no*2;
		int mid=(l+r)/2;
		build(nxt, l, mid, data);
		build(nxt+1, mid+1, r, data);
		tr[no].resize(tr[nxt].size()+tr[nxt+1].size());
		merge(tr[nxt].begin(), tr[nxt].end(), tr[nxt+1].begin(), tr[nxt+1].end(), tr[no].begin());
	}
	//how many numbers in (i, j) are greater or equal than k
	int query(int no, int l, int r, int i, int j, int k)
	{
		if(r<i || l>j)
			return 0;
		if(l>=i && r<=j)
			return (int)(tr[no].end()-upper_bound(tr[no].begin(), tr[no].end(), k));
		int nxt=no*2;
		int mid=(l+r)/2;
		int ql=query(nxt, l, mid, i, j, k);
		int qr=query(nxt+1, mid+1, r, i, j, k);
		return ql+qr;
	}
};