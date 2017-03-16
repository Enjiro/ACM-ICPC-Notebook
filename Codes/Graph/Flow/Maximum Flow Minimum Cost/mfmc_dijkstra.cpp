/*
undirected graph:
u->uu(flow, 0)
uu->vv(flow, cost)
vv->v(flow, 0)
v->xx(flow, 0)
vv->u(flow, 0)
*/
typedef int FTYPE; //type of flow
typedef int CTYPE; //type of cost
typedef pair<FTYPE,CTYPE>pfc;
const CTYPE CINF=INF;
const FTYPE FINF=INF;

void operator+=(pfc &p1, pfc &p2)
{
	p1.F+=p2.F;
	p1.S+=p2.S;
}

class graph
{
	const static int MN=1e+4;
public:
	int n;
	FTYPE flow[MN];
	CTYPE dist[MN], pot[MN];
	int prev[MN], eidx[MN];

	struct Edge
	{
		int to;
		FTYPE cap;
		CTYPE cost;
		Edge(){};
		Edge(int _to, FTYPE _cap, CTYPE _cost)
		{
			to=_to;
			cap=_cap;
			cost=_cost;
		}//
	};
	struct node
	{
		int u;
		CTYPE d;
		node(){};
		node(int _u, CTYPE _d)
		{
			u=_u;
			d=_d;
		}
		bool operator <(const node &foo) const
		{
			return d>foo.d;
		}
	};
	graph(){};
	vector<int>adj[MN];
	vector<Edge>edge;
	inline void set(int _n)
	{
		n=_n;
	}
	inline void reset()
	{
		for(int i=0; i<MN; i++)
			adj[i].clear();
		edge.clear();
	}
	inline void add_edge(int u, int v, FTYPE c, FTYPE cst)
	{
		adj[u].push_back(edge.size());
		edge.push_back(Edge(v, c, cst));
		adj[v].push_back(edge.size());
		edge.push_back(Edge(u, 0, -cst));
	}

	pfc dijkstra(int s, int t)
	{
		for(register int i=0; i<n; i++)
			dist[i]=CINF;
		dist[s]=0;
		flow[s]=FINF;
		priority_queue<node>heap;
		heap.push(node(s, 0));
		while(!heap.empty())
		{
			int u=heap.top().u;
			CTYPE d=heap.top().d;
			heap.pop();
			if(d>dist[u])
				continue;
			for(int i=0; i<adj[u].size(); i++)
			{
				int idx=adj[u][i];
				int v=edge[idx].to;
				CTYPE w=edge[idx].cost;
				if(!edge[idx].cap || dist[v]<=d+w+pot[u]-pot[v])
					continue;
				if(d+w<dist[v])
				{
					dist[v]=d+w;
					prev[v]=u;
					eidx[v]=idx;
					flow[v]=min(flow[u], edge[idx].cap);
					heap.push(node(v, d+w));
				}
			}
		}
		if(dist[t]==CINF)
			return mp(FINF, CINF);
		pfc ret=mp(flow[t], 0);
		for(int u=t; u!=s; u=prev[u])
		{
			int idx=eidx[u];
			edge[idx].cap-=flow[t];
			edge[idx^1].cap+=flow[t];
			ret.second+=flow[t]*edge[idx].cost;
		}
		return ret;
	}

	inline pfc mfmc(int s, int t)
	{
		pfc ret=mp(0, 0);
		pfc got;
		while((got=dijkstra(s, t)).first!=FINF)
			ret+=got;
		return ret;
	}
};