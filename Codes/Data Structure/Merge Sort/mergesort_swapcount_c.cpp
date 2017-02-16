#define INF 0x3F3F3F3F
int temp[100000];
int mergesort(int data[], int l, int r)
{
	if(abs(l-r)<=1)
		return 0;
	int mid=(l+r)/2;
	int ret=mergesort(data, l, mid)+mergesort(data, mid, r);
	for(int i=l; i<r; i++)
		temp[i]=data[i];
	for(int i=l, j=l, k=mid; j<mid || k<r; i++)
	{
		int x=j<mid?temp[j]:INF;
		int y=k<r?temp[k]:INF;
		if(x<y)//x<=y
		{
			data[i]=x;
			j++;
		}
		else
		{
			data[i]=y;
			k++;
			ret+=(mid-j);
		}
	}
	return ret;
}