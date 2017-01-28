class segtree
{
	const static int N=1e+5;
public:
	int tr[4*N];
	segtree(){};
	void reset()
	{
		memset(tr, 0, sizeof(tr));
	}
	void update(int no, int l, int r, int i, int val)
	{
		if(r<i || l>i)
			return;
		if(l>=i && r<=i)
		{
			tr[no]=val;
			return;
		}
		int nxt=(no<<1);
		int mid=(l+r)>>1;
		update(nxt, l, mid, i, val);
		update(nxt+1, mid+1, r, i, val);
		tr[no]=tr[nxt]+tr[nxt+1];
	}
	int query(int no, int l, int r, int i, int j)
	{
		if(r<i || l>j)
			return 0;
		if(l>=i && r<=j)
			return tr[no];
		int nxt=(no<<1);
		int mid=(l+r)>>1;
		return query(nxt, l, mid, i, j)+query(nxt+1, mid+1, r, i, j);
	}
};

const int N=1e+5;
const int M=log2(N)+1;
int n;
segtree tr;
vector< pair<int,int> >g[N];
int lca[N][M];
int h[N], trSz[N];

//in - use X[], Y[] in case
//of edge weights
int X[N], Y[N], W[N];

//hld
int chainInd[N], chainSize[N], chainHead[N], chainPos[N], chainNo, posInBase[N];
int ptr;

void dfs(int u, int l)
{
	trSz[u]=1;
	lca[u][0]=l;
	for(int i=1; i<M; i++)
		lca[u][i]=lca[ lca[u][i-1] ][i-1];
	for(int i=0; i<g[u].size(); i++)
	{
		int v=g[u][i].first;
		if(v==l)
			continue;
		h[v]=h[u]+1;
		dfs(v, u);
		trSz[u]+=trSz[v];
	}
}

inline int getLca(int u, int v)
{
	if(h[u]>h[v])
		swap(u, v);
	for(int i=M-1; i>=0; i--)
		if(h[v]-(1<<i)>=h[u])
			v=lca[v][i];
	if(u==v)
		return u;
	for(int i=M-1; i>=0; i--)
	{
		if(lca[u][i]!=lca[v][i])
		{
			u=lca[u][i];
			v=lca[v][i];
		}
	}
	return lca[u][0];
}

//dont use 'c' if the weight is on the vertex
//instead of the edge
inline void hld(int u, int l, int c)
{
	if(chainHead[chainNo]==-1)
		chainHead[chainNo]=u;
	chainInd[u]=chainNo;
	chainPos[u]=chainSize[chainNo]++;
	tr.update(1, 0, n, ptr, c);
	posInBase[u]=ptr++;

	int msf, idx;
	msf=idx=-1;
	for(int i=0; i<g[u].size(); i++)
	{
		int v=g[u][i].first;
		if(v==l)
			continue;
		if(trSz[v]>msf)
		{
			msf=trSz[v];
			idx=i;
		}
	}
	if(idx>=0)
		hld(g[u][idx].first, u, g[u][idx].second);
	for(int i=0; i<g[u].size(); i++)
	{
		if(i==idx)
			continue;
		int v=g[u][i].first;
		int w=g[u][i].second;
		if(v==l)
			continue;
		chainNo++;
		hld(v, u, w);
	}
}

inline int query_up(int u, int v)
{
	int uchain=chainInd[u];
	int vchain=chainInd[v];
	int ret=0;
	while(true)
	{
		uchain=chainInd[u];
		if(uchain==vchain)
		{
			ret+=tr.query(1, 0, n, posInBase[v]+1, posInBase[u]);
			break;
		}
		int head=chainHead[uchain];
		ret+=tr.query(1, 0, n, posInBase[head],posInBase[u]);
		u=head;
		u=lca[u][0];
	}
	return ret;
}

//returns sum of all edges weights
//from 'u' to 'v'
inline int query(int u, int v)
{
	if(u==v)
		return 0;
	int l=getLca(u, v);
	return query_up(u, l)+query_up(v, l);
}

//set and edge to value 'val'
inline void update(int u, int val)
{
	int x=X[u], y=Y[u];
	if(lca[x][0]==y)
		tr.update(1, 0, n, posInBase[x], val);
	else
		tr.update(1, 0, n, posInBase[y], val);
}

void clearHld()
{
	//tr.reset();
	for(int i=0; i<=n; i++)
	{
		g[i].clear();
		chainHead[i]=-1;
		chainSize[i]=0;
	}
	ptr=1;
	chainNo=0;
}

int main()
{
	scanf("%d", &n);
	clearHld();
	for(int i=1; i<n; i++)
	{
		scanf("%d %d %d", &X[i], &Y[i], &W[i]);
		g[ X[i] ].push_back({Y[i], W[i]});
		g[ Y[i] ].push_back({X[i], W[i]});
	}
	dfs(1, 0);
	hld(1, 0, 0);
	int q;
	scanf("%d", &q);
	while(q--)
	{
		int o, x, y;
		scanf("%d %d %d", &o, &x, &y);
		if(o==1)
			printf("%d\n", query(x, y));
		else
			update(x, y);
	}
	return 0;
}