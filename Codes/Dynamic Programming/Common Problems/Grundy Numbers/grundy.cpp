const int MN=1e+5;
bool memo[MN];
int dp[MN];
int grundy(int x)
{
	if(x==0)
		return 0;
	if(memo[x])
		return dp[x];
	set<int>mex;
	for(;;)//moves
		mex.insert(grundy(x-(moves)));
	int &ret=dp[x]=0;
	while(mex.count(ret))
		ret++;
	memo[x]=true;
	return ret;
}