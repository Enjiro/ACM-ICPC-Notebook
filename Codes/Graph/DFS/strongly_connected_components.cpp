class graph
{
	const static int MN=1e+5;
public:
	vector<int>data[MN], aux;
	bool vis[MN];
	int grp[MN];
	int dfs_num[MN], dfs_low[MN];
	int dfs_cnt, numSCC;

	graph(){};
	void clear()
	{
		for(int i=0; i<MN; i++)
		{
			data[i].clear();
			dfs_num[i]=-1;
			dfs_low[i]=0;
			vis[i]=false;
		}
		aux.clear();
		dfs_cnt=numSCC=0;
	}
	void add_edge(int u, int v)
	{
		data[u].push_back(v);
	}
	void tarjanSCC(int u)
	{
		dfs_num[u]=dfs_low[u]=dfs_cnt++;
		aux.push_back(u);
		vis[u]=true;

		for(int i=0; i<data[u].size(); i++)
		{
			int v=data[u][i];
			if(dfs_num[v]==-1)
				tarjanSCC(v);
			if(vis[v])
				dfs_low[v]=min(dfs_low[v], dfs_low[u]);
		}

		if(dfs_num[u]==dfs_low[u])
		{
			while(1)
			{
				int v=aux.back();
				aux.pop_back();
				vis[v]=false;
				grp[v]=numSCC;
				if(u==v)
					break;
			}
			numSCC++;
		}
	}
};