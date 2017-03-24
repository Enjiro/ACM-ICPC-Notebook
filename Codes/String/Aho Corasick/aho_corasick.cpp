class aho_corasick
{
private:
	static const int MNT=1e+6;
	static const int MNC=26;
public:
	int trie[MNT][MNC];
	int term[MNT];
	int link[MNT];
	int sum[MNT];
	int cnt=1;
	aho_corasick(){};
	void clear()
	{
		RESET(trie, 0);
		RESET(term, 0);
		RESET(link, 0);
		RESET(sum, 0);
		cnt=1;
	}
	int node(int x, int j)
	{
		return trie[x][j];
	}
	int end(int x, int j)
	{
		return term[ node(x,j) ];
	}
	void insert(char *str)
	{
		int sz=strlen(str);
		int no=0;
		for(int i=0; i<sz; i++)
		{
			int x=str[i]-'a';
			if(!trie[no][x])
				trie[no][x]=cnt++;
			sum[ trie[no][x] ]++;
			no=trie[no][x];
		}
		term[no]++;
	}
	bool find(char *str)
	{
		int sz=strlen(str);
		int no=0;
		for(int i=0; i<sz; i++)
		{
			int x=str[i]-'a';
			if(!sum[ trie[no][x] ])
				return false;
			no=trie[no][x];
		}
		return true;
	}
	void erase(char *str)
	{
		int sz=strlen(str);
		int no=0;
		for(int i=0; i<sz; i++)
		{
			int x=str[i]-'a';
			sum[ trie[no][x] ]--;
			no=trie[no][x];
		}
		term[no]--;
	}
	void update_link()
	{
		queue<int>aho;
		aho.push(0);
		while(!aho.empty())
		{
			int x=aho.front();
			aho.pop();
			term[x]|=term[ link[x] ];
			for(int i=0; i<MNC; i++)
			{
				if(trie[x][i])
				{
					int y=trie[x][i];
					aho.push(y);
					link[y]=x?trie[ link[x] ][i]:0;
				}
				else
				{
					trie[x][i]=trie[ link[x] ][i];
				}
			}
		}
	}
};