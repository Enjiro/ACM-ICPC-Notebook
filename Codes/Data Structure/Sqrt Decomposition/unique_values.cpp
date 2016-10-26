const int N=100000;
int SN=sqrt(N);

class mo
{
public:
	int l, r, i;
	mo(){};
	mo(int _l, int _r, int _i)
	{
		l=_l, r=_r, i=_i;
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

int data[N], freq[N], ans[N];
int cnt=0;
void update(int p, int s)
{
	int x=data[p];
	if(s==1)
	{
		if(freq[x]==0)
			cnt++;
	}
	else
	{
		if(freq[x]==1)
			cnt--;
	}
	freq[x]+=s;
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
		scanf("%d", &data[i]);

	int q;
	scanf("%d", &q);
	vector<mo>querys;
	for(int i=0; i<q; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);
		querys.push_back(mo(l, r, i));
	}
	sort(querys.begin(), querys.end());

	int l=1, r=1;
	cnt=0;
	memset(freq, 0, sizeof(freq));
	update(l, 1);
	for(int i=0; i<q; i++)
	{
		int li=querys[i].l;
		int ri=querys[i].r;
		int ii=querys[i].i;
		while(l>li)
			update(--l, 1);
		while(r<ri)
			update(++r, 1);
		while(l<li)
			update(l++, -1);
		while(r>ri)
			update(r--, -1);
		ans[ii]=cnt;
	}
	for(int i=0; i<querys.size(); i++)
		printf("%d\n", ans[i]);
	return 0;
}