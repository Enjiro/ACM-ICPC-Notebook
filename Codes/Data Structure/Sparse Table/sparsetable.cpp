class sparsetable
{
	#define lbit(x) 63-__builtin_clzll(x);
	const static int N=100000, LN=20;
	int data[N][LN], n, ln;
public:
	sparsetable(){};
	void clear()
	{
		memset(data, 0, sizeof(data));
	}
	void build(vector<int>&foo)
	{
		n=foo.size();
		ln=lbit(n);
		for(int i=0; i<n; i++)
			data[i][0]=foo[i];
		for(int j=1; j<=ln; j++)
			for(int i=0; i<n-(1<<j)+1; i++)
				data[i][j]=max(data[i][j-1], data[i+(1<<(j-1))][j-1]);
	}
	int query(int l, int r)
	{
		int i=abs(l-r)+1;
		int j=lbit(i);
		return max(data[l][j], data[l-(1<<j)+1][j]);
	}
};