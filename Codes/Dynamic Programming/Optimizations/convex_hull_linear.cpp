//Original recurrence:
//	  dp[i]=min(dp[j]+b[j]*a[i]) for j<i
//Condition:
//	  b[j]>=b[j+1]
//	  a[i]<=a[i+1]
// Solution:
// Hull cht=Hull();
// cht.insertLine(b[0], dp[0])
// for(int i=1; i<n; i++)
// {
// 	  dp[i]=cht.query(a[i]);
// 	  cht.insertLine(b[i], dp[i])
// }
// answer is dp[n-1]

class Hull
{
	const static int CN=1e+5+35;
public:
	long long a[CN], b[CN];
	double x[CN];
	int head, tail;
	Hull():head(1), tail(0){};

	long long query(long long xx)
	{
		if(head>tail)
			return 0;
		while(head<tail && x[head+1]<=xx)
			head++;
		x[head]=xx;
		return a[head]*xx+b[head];
	}

	void insertLine(long long aa, long long bb)
	{
		double xx=-1e18;
		while(head<=tail)
		{
			if(aa==a[tail])
				return;
			xx=1.0*(b[tail]-bb)/(aa-a[tail]);
			if(head==tail || xx>=x[tail])
				break;
			tail--;
		}
		a[++tail]=aa;
		b[tail]=bb;
		x[tail]=xx;
	}
};