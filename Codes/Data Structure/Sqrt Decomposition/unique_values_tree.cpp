#define pb push_back
#define ALL(x) x.begin(),x.end()

const int N=1e+5+35;
const int M=20;
const int SN=sqrt(2*N)+1;

class mo
{
public:
	int l, r, i, lc;
	mo(){};
	mo(int _l, int _r, int _lc, int _i)
	{
		l=_l, r=_r, lc=_lc, i=_i;
	}
	bool operator <(const mo &foo) const
	{
		if((r/SN)!=(foo.r/SN))
			return (r/SN)<(foo.r/SN);
		if(l!=foo.l)
			return l<foo.l;
		return i<foo.i;
	}
};

int n, q;
int h[N], lca[N][M];
vector<int>g[N];
int dl[N], dr[N], di[2*N], cur;

void dfs(int u, int p)
{
	dl[u]=++cur;
	di[cur]=u;
	lca[u][0]=p;
	for(int i=1; i<M; i++)
		lca[u][i]=lca[ lca[u][i-1] ][i-1];
	for(int i=0; i<g[u].size(); i++)
	{
		int v=g[u][i];
		if(v==p)
			continue;
		h[v]=h[u]+1;
		dfs(v, u);
	}
	dr[u]=++cur;
	di[cur]=u;
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

map<string,int>remap;
int data[N], ans[N], vis[N], freq[N], cnt;
inline void update(int u)
{
	int x=data[u];
	if(vis[u] && (--freq[ data[u] ]==0))
		cnt--;
	else if(!vis[u] && (freq[ data[u] ]++==0))
		cnt++;
	vis[u]^=1;
}

int main()
{
	scanf("%d %d", &n, &q);
	for(int i=1; i<=n; i++)
	{
		char temp[25];
		scanf("%s", temp);
		string temp2=string(temp);
		if(!remap.count(temp2))
			remap[temp2]=remap.size();
		data[i]=remap[temp2];
	}
	for(int i=1; i<n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1, 0);

	vector<mo>query;
	for(int i=0; i<q; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		int lc=getLca(u, v);
		if(dl[u]>dl[v])
			swap(u, v);
		query.pb(mo(u==lc?dl[u]:dr[u], dl[v], lc, i));
	}
	sort(ALL(query));

	int l=query[0].l, r=query[0].l-1;
	cnt=0;
	for(int i=0; i<q; i++)
	{
		int li=query[i].l;
		int ri=query[i].r;
		int lc=query[i].lc;
		int ii=query[i].i;
		while(l>li)
			update(di[--l]);
		while(r<ri)
			update(di[++r]);
		while(l<li)
			update(di[l++]);
		while(r>ri)
			update(di[r--]);

		int u=di[l], v=di[r];
		if(lc!=u && lc!=v)
			update(lc);
		ans[ii]=cnt;
		if(lc!=u && lc!=v)
			update(lc);
	}
	for(int i=0; i<q; i++)
		printf("%d\n", ans[i]);
	return 0;
}