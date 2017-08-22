const int MN=2*1e+5+35;
int n, m;
vector<int>g[MN], rg[MN];
bool vis[MN];
int grp[MN];
stack<int>kos;
void dfsOne(int u)
{
	vis[u]=true;
	for(int i=0; i<g[u].size(); i++)
	{
		int v=g[u][i];
		if(!vis[v])
			dfsOne(v);
	}
	kos.push(u);
}

void dfsTwo(int u, int k)
{
	vis[u]=true;
	for(int i=0; i<rg[u].size(); i++)
	{
		int v=rg[u][i];
		if(!vis[v])
			dfsTwo(v, k);
	}
	grp[u]=k;
}

void kosaraju()
{
	for(int i=0; i<2*n; i++)
		if(!vis[i])
			dfsOne(i);
	int k=1;
	SET(vis, false);
	while(!kos.empty())
	{
		int u=kos.top();
		kos.pop();
		if(!vis[u])
			dfsTwo(u, k++);
	}
}

bool _2sat()
{
	kosaraju();
	for(int i=0; i<n; i++)
		if(grp[i]==grp[i+n])
			return false;
	return true;
}
