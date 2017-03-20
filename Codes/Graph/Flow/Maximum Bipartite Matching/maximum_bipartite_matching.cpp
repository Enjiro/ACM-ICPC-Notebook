const int MN=1e+3;
vector<int>g[MN];
int match[MN], rmatch[MN], vis[MN];
int findmatch(int u)
{
	if(vis[u])
		return 0;
	vis[u]=true;
	for(int v:g[u])
	{
		if(match[v]==-1 || findmatch(match[v]))
		{
			match[v]=u;
			rmatch[u]=v;
			return 1;
		}
	}
	return 0;
}

int maxMatch(int n)
{
	int ret=0;
	memset(match, -1, sizeof(match));
	for(int i=0; i<n; i++)
	{
		memset(vis, false, sizeof(vis));
		ret+=findmatch(i);
	}
	return ret;
}