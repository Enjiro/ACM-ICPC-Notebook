int stoer_wagner(int n)
{
	int ret=INF;
	for(int i=0; i<n; i++)
		v[i]=i;

	while(n>1)
	{
		a[ v[0] ]=true;
		for(int i=1; i<n; i++)
		{
			a[ v[i] ]=false;
			na[i-1]=i;
			w[i]=graph[ v[0] ][ v[i] ];
		}

		int prev=v[0];
		for(int i=1; i<n; i++)
		{
			int zj=-1;
			for(int j=1; j<n; j++)
			{
				if(!a[ v[j] ] && (zj<0 || w[j]>w[zj]))
					zj=j;
			}

			a[ v[zj] ]=true;

			if(i==n-1)
			{
				ret=min(ret, w[zj]);

				for(int j=0; j<n; j++)
					graph[ v[j] ][prev]=graph[prev][ v[j] ]+=graph[ v[zj] ][ v[j] ];
				v[zj]=v[--n];
				break;
			}
			prev=v[zj];

			for(int j=1; j<n; j++)
				if(!a[ v[j] ])
					w[j]+=graph[ v[zj] ][ v[j] ];
		}
	}
	return ret;
}