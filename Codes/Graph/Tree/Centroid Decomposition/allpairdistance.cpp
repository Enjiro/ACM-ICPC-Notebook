/// David Mateus Batista <david.batista3010@gmail.com>
/// Computer Science - Federal University of Itajuba - Brazil

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define INF 0x3F3F3F3F
#define LINF 0x3F3F3F3F3F3F3F3FLL
#define DINF (double)1e+30
#define EPS (double)1e-9
#define PI (double)acos(-1.0)
#define RAD(x) (double)(x*PI)/180.0
#define PCT(x,y) (double)x*100.0/y

#define pb push_back
#define mp make_pair
#define pq priority_queue
#define F first
#define S second

#define D(x) x&(-x)
#define SZ(x) (int)x.size()
#define ALL(x) x.begin(),x.end()
#define SET(a,b) memset(a, b, sizeof(a))

#define gcd(x,y) __gcd(x, y)
#define lcm(x,y) (x/gcd(x,y))*y

#define bitcnt(x) __builtin_popcountll(x)
#define lbit(x) 63-__builtin_clzll(x)
#define zerosbitll(x) __builtin_ctzll(x)
#define zerosbit(x) __builtin_ctz(x)

enum {North, East, South, West};
//{0, 1, 2, 3}
//{Up, Right, Down, Left}

int mi[] = {-1, 0, 1, 0, -1, 1, 1, -1};
int mj[] = {0, 1, 0, -1, 1, 1, -1, -1};

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

int n;
int haha[10000];
graph data;

void update(int x)
{
	data.update(x);
	haha[x]^=1;
}

ll naive(int x)
{
	ll ret=0;
	for(int i=1; i<=n; i++)
	{
		ret+=haha[i]*data.getDist(x, i);
	}
	return ret;
}

int main()
{
	scanf("%d", &n);
	for(int i=1; i<n; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		x++, y++;
		data.addEdge(x, y);
	}
	data.buildLca(1, 1);
	data.buildCentroid(1, 1);

	int q;
	scanf("%d", &q);
	while(q--)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		y++;
		if(x==0)
			update(y);
		else
			printf("%lld\n", data.query(y));
	}
	return 0;
}