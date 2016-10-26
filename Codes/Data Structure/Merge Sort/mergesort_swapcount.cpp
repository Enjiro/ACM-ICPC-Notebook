#define INF 0x3F3F3F3F
int mergesort(vector<int>&data)
{
	if(data.size()==1)
		return 0;
	vector<int>L, R;
	int t=data.size();
	for(int i=0; i<t/2; i++)
		L.push_back(data[i]);
	for(int i=t/2; i<t; i++)
		R.push_back(data[i]);
	int ret=mergesort(L)+mergesort(R);
	for(int i=0, j=0, k=0; j<L.size() || k<R.size(); i++)
	{
		int x=j<L.size()?L[j]:INF;
		int y=k<R.size()?R[k]:INF;
		if(x<y)
		{
			data[i]=x;
			j++;
		}
		else
		{
			data[i]=y;
			k++;
			ret+=(L.size()-j);
		}
	}
	return ret;
}