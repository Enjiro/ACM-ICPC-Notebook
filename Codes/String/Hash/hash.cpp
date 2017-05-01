typedef unsigned long long ull;
class hashc
{
public:
	vector<ull>prefix;
	vector<ull>power;
	int k=37;
	int t;
	hashc(){};
	hashc(vector<int>&data)
	{
		t=data.size();
		prefix.resize(t+1, 0);
		power.resize(t+1, 0);
		prefix[0]=0;
		power[0]=1;
		for(int i=0; i<t; i++)
		{
			prefix[i+1]=prefix[i]*k+data[i];
			power[i+1]=power[i]*k;
		}
	}

	hashc build(string &str)
	{
		vector<int>data(str.size());
		for(int i=0; i<str.size(); i++)
			data[i]=(str[i]-'a'+1);
		return hashc(data);
	}

	ull get()
	{
		return prefix[t];
	}
	ull calc(int l, int r)
	{
		return prefix[r]-(prefix[l-1]*power[r-l+1]);
	}
	bool same(int xl, int xr, int yl, int yr)
	{
		return this->calc(xl, xr)==this->calc(yl, yr);
	}
	int find(hashc &pattern)
	{
		int pt=pattern.t;
		ull val=pattern.calc(1, pt);
		for(int i=1; i<=t-pt+1; i++)
		{
			if(this->calc(i, i+pt-1)==val)
				return i-1;
		}
		return -1;
	}
};