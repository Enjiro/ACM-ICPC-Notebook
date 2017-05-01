int lps[1000000];
void lps_calc(string &str)
{
	lps[0]=0;
	for(int i=1, j=0, f=0; i<str.size(); i+=f, f=0)
	{
		if(str[i]==str[j])
		{	
			lps[i]=j;
			j++;
			f=1;
		}
		else
		{
			if(j>0)
			{
				j=lps[j-1];
			}
			else
			{
				lps[i]=0;
				f=1;
			}
		}
	}
}

//finding str in pat
void kmp(string &str, string &pat)
{
	lps_calc(pat);
	int i=0, j=0;
	while(i<str.size())
	{
		if(str[i]==pat[j])
		{
			i++;
			j++;
		}
		if(j==pat.size())
		{
			printf("Padrao encontrado em: [%d, %d]", i-j, (i-j)+pat.size()-1);
			j=lps[j-1];
		}
		else if(i<str.size() && str[i]!=pat[j])
		{
			if(j!=0)
				j=lps[j-1];
			else
				i++;
		}
	}
}