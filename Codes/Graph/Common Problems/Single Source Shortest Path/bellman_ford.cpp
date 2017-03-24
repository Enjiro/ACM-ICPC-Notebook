class node
{
public:
	int x, y, d;
	node(){};
	node(int _x, int _y, int _d)
	{
		x=_x, y=_y, d=_d;
	}
};

int n, v;
vector<node>graph;
int dist[1035];
bool bellmanford(int s)
{
	memset(dist, INF, sizeof(dist));
	dist[s]=0;
	for(int i=0; i<n-1; i++)
	{
		for(int j=0; j<graph.size(); j++)
		{
			int x=graph[j].x;
			int y=graph[j].y;
			int d=graph[j].d;
			if(dist[y]>dist[x]+d)
				dist[y]=dist[x]+d;
		}
	}

	for(int i=0; i<graph.size(); i++)
	{
		int x=graph[i].x;
		int y=graph[i].y;
		int d=graph[i].d;
		if(dist[x]<INF && dist[y]>dist[x]+d)
			return true;
	}
	return false;
}