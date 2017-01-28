const int N=1e+5;
const int M=log2(N)+1;

set<int>g[N]; //graph
int h[N]; //heigh of nodes
int trSz[N], sz; //tree subsize, size of current tree
int lca[N][M]; //lca sparse table
int cg[N]; //centroid graph

void dfs(int u, int l)
{
	lca[u][0]=l;
	for(int i=1; i<M; i++)
		lca[u][i]=lca[ lca[u][i-1] ][i-1];
	for(auto v:g[u])
	{
		if(v==l)
			continue;
		h[v]=h[u]+1;
		dfs(v, u);
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

inline int getDist(int u, int v)
{
	return h[u]+h[v]-2*h[getLca(u, v)];
}

void centDfs(int u, int l)
{
	trSz[u]=1;
	sz++;
	for(auto v:g[u])
	{
		if(v==l)
			continue;
		centDfs(v, u);
		trSz[u]+=trSz[v];
	}
}

int findCentroid(int u, int l)
{
	for(auto v:g[u])
	{
		if(v==l)
			continue;
		if(trSz[v]*2>=sz)
			return findCentroid(v, u);
	}
	return u;
}

inline void buildCentroid(int u, int l)
{
	sz=0;
	centDfs(u, u);
	int c=findCentroid(u, u); //actual centroid
	cg[c]=(c==l?c:l);
	for(auto v:g[c])
	{
		g[v].erase(g[v].find(c));
		buildCentroid(v, c);
	}
	g[c].clear();
}