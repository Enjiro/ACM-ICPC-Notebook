class graph
{
	const static int N=100000;
public:
	vector< pair<int,int> >edge;
	vector<int>adj[N];
	int ptr[N];
	int dist[N];

	graph(){};
	void clear()
	{
		for(int i=0; i<N; i++)
			adj[i].clear();
		edge.clear();
	}
	void add_edge(int u, int v, int c)
	{
		adj[u].push_back(edge.size());
		edge.push_back(mp(v, c));
		adj[v].push_back(edge.size());
		edge.push_back(mp(u, 0)); //(u, c) if is non-directed
	}
	bool dinic_bfs(int s, int t)
	{
		memset(dist, -1, sizeof(dist));
		dist[s]=0;

		queue<int>bfs;
		bfs.push(s);
		while(!bfs.empty() && dist[t]==-1)
		{
			int u=bfs.front();
			bfs.pop();
			for(int i=0; i<adj[u].size(); i++)
			{
				int idx=adj[u][i];
				int v=edge[idx].F;

				if(dist[v]==-1 && edge[idx].S>0)
				{
					dist[v]=dist[u]+1;
					bfs.push(v);
				}
			}
		}
		return dist[t]!=-1;
	}
	int dinic_dfs(int u, int t, int flow)
	{
		if(u==t)
			return flow;
		for(int &i=ptr[u]; i<adj[u].size(); i++)
		{
			int idx=adj[u][i];
			int v=edge[idx].F;
			if(dist[v]==dist[u]+1 && edge[idx].S>0)
			{
				int cf=dinic_dfs(v, t, min(flow, edge[idx].S));
				if(cf>0)
				{
					edge[idx].S-=cf;
					edge[idx^1].S+=cf;
					return cf;
				}
			}
		}
		return 0;
	}
	int maxflow(int s, int t)
	{
		int ret=0;
		while(dinic_bfs(s, t))
		{
			memset(ptr, 0, sizeof(ptr));
			int cf=dinic_dfs(s, t, INF);
			if(cf==0)
				break;
			ret+=cf;
		}
		return ret;
	}
};