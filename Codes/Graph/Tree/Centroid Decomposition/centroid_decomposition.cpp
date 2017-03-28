class graph
{
	const static int N=1e+5;
	const static int LN=log2(N)+1;
public:
	vector<int>g[N];
	int h[N], lca[N][LN];

	int sz[N];
	int cg[N], gsz, dlt[N];
	graph(){};
	inline void addEdge(int u, int v)
	{
		g[u].pb(v);
		g[v].pb(u);
	}
	void buildLca(int u, int f)
	{
		lca[u][0]=f;
		for(int i=1; i<LN; i++)
			lca[u][i]=lca[ lca[u][i-1] ][i-1];
		for(int v:g[u])
		{
			if(v==f)
				continue;
			h[v]=h[u]+1;
			buildLca(v, u);
		}
	}
	inline int getLca(int u, int v)
	{
		if(h[u]>h[v])
			swap(u, v);
		for(int i=LN-1; i>=0; i--)
			if(h[v]-(1<<i)>=h[u])
				v=lca[v][i];
		if(u==v)
			return u;
		for(int i=LN-1; i>=0; i--)
		{
			if(lca[u][i]!=lca[v][i])
			{
				u=lca[u][i];
				v=lca[v][i];
			}
		}
		return lca[u][0];
	}
	inline int getDist(int u, int v)
	{
		return h[u]+h[v]-2*h[getLca(u, v)];
	}
	void buildSz(int u, int f)
	{
		gsz++;
		sz[u]=1;
		for(int v:g[u])
		{
			if(v==f || dlt[v])
				continue;
			buildSz(v, u);
			sz[u]+=sz[v];
		}
	}
	int findCentroid(int u, int f)
	{
		for(int v:g[u])
		{
			if(v==f || dlt[v])
				continue;
			if(sz[v]*2>=gsz)
				return findCentroid(v, u);
		}
		return u;
	}
	inline void buildCentroid(int u, int f)
	{
		gsz=0;
		buildSz(u, u);
		int c=findCentroid(u, u);
		cg[c]=(u==f)?c:f;
		dlt[c]=1;
		for(int v:g[c])
		{
			if(v==c || dlt[v])
				continue;
			buildCentroid(v, c);
		}
	}
};