double minimumWidth(polygon &ch)
{
	double ret=DINF;
	int sz=ch.size();
	int j=1;
	for(int i=0; i<sz; i++)
	{
		int nxt=(j+1)%sz;
		while(distPointLine(ch[i], ch[(i+1)%sz], ch[j])<distPointLine(ch[i], ch[(i+1)%sz], ch[nxt]))
		{
			j=(j+1)%sz;
			nxt=(j+1)%sz;
		}
		ret=min(ret, distPointLine(ch[i], ch[(i+1)%sz], ch[j]));
	}
	return ret;
}