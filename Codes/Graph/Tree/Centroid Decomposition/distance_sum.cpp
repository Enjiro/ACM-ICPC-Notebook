class graph
{
	const static int N=1e+5+35;
	const static int LN=log2(N)+1;
public:
	//tree
	vector<int>g[N];
	int h[N], lca[N][LN];

	//centroid
	vector<int>cgt[N];
	int sz[N];
	int cg[N], gsz, dlt[N];

	//updates & querys
	ll sum[N], cnt[N];
	int vis[N], idx[N];
	vector<ll>psum[N], pcnt[N];

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

		if(c!=cg[c])
		{
			idx[c]=cgt[f].size();
			cgt[f].pb(c);
			psum[f].pb(0);
			pcnt[f].pb(0);
		}

		dlt[c]=1;
		for(int v:g[c])
		{
			if(v==c || dlt[v])
				continue;
			buildCentroid(v, c);
		}
	}

	void update(int u)
	{
		int v=u, l=-1;
		int k=(vis[u]==0)?1:-1;
		while(1)
		{
			ll d=k*getDist(u, v);
			sum[v]+=d;
			if(l!=-1)
			{
				psum[v][idx[l]]+=d;
				pcnt[v][idx[l]]+=k;
			}
			cnt[v]+=k;
			if(v==cg[v])
				break;
			l=v;
			v=cg[v];
		}
		vis[u]^=1;
	}
	ll query(int u)
	{
		ll ret=0;
		int v=u, l=-1;
		while(1)
		{
			ll d=getDist(u, v);
			ret+=sum[v]+cnt[v]*d;
			if(l!=-1)
			{
				ret-=psum[v][idx[l]];
				ret-=pcnt[v][idx[l]]*d;
			}
			if(v==cg[v])
				break;
			l=v;
			v=cg[v];
		}
		return ret;
	}
};