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