const int MN=1e+5+35;
const int LMN=1+log2(MN);
vector<int>graph[MN];
int LVL[MN];
int T[MN];
int dp[MN][LMN];
bool vis[MN];

void dfs(int u, int f, int d)
{
	vis[u]=true;
	LVL[x]=d;
	dp[x][0]=f;
	for(int i=1; i<LMN; i++)
		dp[x][i]=dp[ dp[x][i-1] ][i-1];

	vis[x]=true;
	for(int i=0; i<graph[x].size(); i++)
	{
		int v=graph[x][u];
		if(!vis[v])
			dfs(v, x, d+1);
	}
}

inline int lca(int u, int v)
{
    if(LVL[u]>LVL[v])
        swap(u, v);
    for(int i=LMN-1; i>=0; i--)
        if(LVL[v]-(1<<i)>=LVL[u])
            v=dp[v][i];
    if(u==v)
        return u;
    for(int i=LMN-1; i>=0; i--)
    {
        if(dp[u][i]!=dp[v][i])
        {
            u=dp[u][i];
            v=dp[v][i];
        }
    }
    return dp[u][0];
}