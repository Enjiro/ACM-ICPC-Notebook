polygon convexHull(polygon T)
{
	int n=T.size(), k=0;
	polygon H(2*n);

	sort(T.begin(), T.end());
	//lower_hull
	for(int i=0; i<n; i++)
	{
		while(k>=2 && ccw(H[k-1], T[i], H[k-2])<=0)
			k--;
		H[k++]=T[i];
	}
	//upper_hull
	for(int i=n-2, t=k+1; i>=0; i--)
	{
		while(k>=t && ccw(H[k-1], T[i], H[k-2])<=0)
			k--;
		H[k++]=T[i];
	}
	H.resize(k);
	return H;
}