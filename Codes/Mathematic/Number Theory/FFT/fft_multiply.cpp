#define PI (double)acos(-1.0)
typedef complex<double> base;
void fft(vector<base>&data, bool invert)
{
	int n=data.size();
	for(int i=1, j=0; i<n; i++)
	{
		int bit=n>>1;
		for(; j>=bit; bit>>=1)
			j-=bit;
		j+=bit;
		if(i<j)
			swap(data[i], data[j]);
	}

	for(int len=2; len<=n; len<<=1)
	{
		double ang=2*PI/len*(invert?-1:1);
		base wlen(cos(ang), sin(ang));
		for(int i=0; i<n; i+=len)
		{
			base w(1);
			for(int j=0; j<len/2; j++)
			{
				base u=data[i+j], v=data[i+j+len/2]*w;
				data[i+j]=u+v;
				data[i+j+len/2]=u-v;
				w*=wlen;
			}
		}
	}
	if(invert)
		for(int i=0; i<n; i++)
			data[i]/=n;
}

vector<int>fft_multiply(vector<int>&a, vector<int>&b)
{
	vector<base>fa(a.begin(), a.end());
	vector<base>fb(b.begin(), b.end());
	int n=1;
	while(n<max(a.size(), b.size()))
		n<<=1;
	n<<=1;
	fa.resize(n);
	fb.resize(n);
	fft(fa, false);
	fft(fb, false);
	for(int i=0; i<n; i++)
		fa[i]*=fb[i];
	fft(fa, true);

	vector<int>ret(n);
	for(int i=0; i<n; i++)
		ret[i]=(int)(fa[i].real()+0.5);

	int carry=0;
	for(int i=0; i<n; i++)
	{
		ret[i]+=carry;
		carry=ret[i]/10;
		ret[i]%=10;
	}
	return ret;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	vector<int>a,b;

	for(int i=0; i<n; i++)
	{
		int x;
		scanf("%d", &x);
		a.pb(x);
	}

	for(int i=0; i<m; i++)
	{
		int x;
		scanf("%d", &x);
		b.pb(x);
	}
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	vector<int>ans=fft_multiply(a, b);
	reverse(ans.begin(), ans.end());
	bool flag=false;
	for(int i=0; i<ans.size(); i++)
	{
		if(ans[i])
			flag=true;
		if(flag)
			printf("%d", ans[i]);
	}
	printf("\n");
	return 0;
}