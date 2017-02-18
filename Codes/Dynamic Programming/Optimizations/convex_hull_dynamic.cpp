//Original recurrence:
//	  dp[i]=min(dp[j]+b[j]*a[i]) for j<i
//Condition:
//	  b[j]>=b[j+1]
//	  a[i]<=a[i+1]
// Solution:
// HullDynamic cht;
// cht.insertLine(b[0], dp[0])
// for(int i=1; i<n; i++)
// {
// 	  dp[i]=cht.query(a[i]);
// 	  cht.insertLine(b[i], dp[i])
// }
// answer is dp[n-1]

const long long is_query=-(1LL<<62);
class Line
{
public:
	long long m, b;
	mutable function<const Line*()>succ;
	bool operator < (const Line &rhs) const
	{
		if(rhs.b!=is_query)
			return m<rhs.m;
		const Line *s=succ();
		if(!s)
			return 0;
		long long x=rhs.m;
		return (b-s->b)<((s->m-m)*x);
	}
};

class HullDynamic: public multiset<Line>
{
public:
	void clear()
	{
		clear();
	}
	bool bad(iterator y)
	{
		auto z=next(y);
		if(y==begin())
		{
			if(z==end())
				return 0;
			return (y->m==z->m && y->b<=z->b);
		}
		auto x=prev(y);
		if(z==end())
			return (y->m == x->m && y->b<=x->b);
		return ((x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m));
	}
	void insertLine(ll m, ll b)
	{
		auto y=insert({m, b});
		y->succ=[=]
		{
			return next(y)==end()?0:&*next(y);
		};
		if(bad(y))
		{
			erase(y);
			return;
		}
		while(next(y)!=end() && bad(next(y)))
			erase(next(y));
		while(y!=begin() && bad(prev(y)))
			erase(prev(y));
	}
	long long query(long long x)
	{
		auto ret=*lower_bound((Line){x, is_query});
		return ret.m*x+ret.b;
	}
};