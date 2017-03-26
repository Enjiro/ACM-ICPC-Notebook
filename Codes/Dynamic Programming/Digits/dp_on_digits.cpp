char str[100];
int dp[100][300][2];
bool memo[100][300][2];
int n, k;

//numeros de 0 a x, tal que a soma dos digitos eh igual a k
int solve(int i, int s, int t)
{
	if(i==n)
	{
		if(!t && s==k)
			return 1;
		return 0;
	}
	if(s>k)
		return 0;
	if(memo[i][s][t])
		return dp[i][s][t];
	int &ret=dp[i][s][t]=0;
	if(t)
	{
		for(int j=0; j<=str[i]-'0'; j++)
		{
			if(j==str[i]-'0')
				ret+=solve(i+1, s+j, 1);
			else
				ret+=solve(i+1, s+j, 0);
		}
	}
	else
	{
		for(int j=0; j<10; j++)
		{
			ret+=solve(i+1, s+j, 0);
		}
	}
	memo[i][s][t]=true;
	return ret;
}

//quantos bits ativos existem entre 0 e x
string str2;
int n2;
int dp2[100][300][2];
bool memo2[100][300][2];
int solve2(int i, int s, int t)
{
	if(i==n2)
		return s;
	if(memo2[i][s][t])
		return dp2[i][s][t];
	int &ret=dp2[i][s][t]=0;
	if(t)
	{
		for(int j=0; j<=str2[i]-'0'; j++)
		{
			if(j==str2[i]-'0')
				ret+=solve2(i+1, s+(j==1), 1);
			else
				ret+=solve2(i+1, s+(j==1), 0);
		}
	}
	else
	{
		for(int j=0; j<2; j++)
		{
			ret+=solve2(i+1, s+(j==1), 0);
		}
	}
	memo2[i][s][t]=true;
	return ret;
}

//numeros de 1 a x, tal que a soma dos digitos eh multiplo de k
char str3[100];
int n3;
int dp3[100][300][2];
bool memo3[100][300][2];
int solve3(int i, int s, int t)
{
	if(i==n3)
		return !s;
	if(memo3[i][s][t])
		return dp3[i][s][t];
	int &ret=dp3[i][s][t]=0;
	if(t)
	{
		for(int j=0; j<=str3[i]-'0'; j++)
		{
			if(j==str3[i]-'0')
				ret+=solve3(i+1, (s+j)%k, 1);
			else
				ret+=solve3(i+1, (s+j)%k, 0);
		}
	}
	else
	{
		for(int j=0; j<10; j++)
		{
			ret+=solve3(i+1, (s+j)%k, 0);
		}
	}
	memo3[i][s][t]=true;
	return ret;
}

//numeros de 1 a x, tal que o xor dos digitos eh igual a k
char str4[100];
int n4;
int dp4[100][300][2];
bool memo4[100][300][2];
int solve4(int i, int s, int t)
{
	if(i==n4)
		return s==k;
	if(memo4[i][s][t])
		return dp4[i][s][t];
	int &ret=dp4[i][s][t]=0;
	if(t)
	{
		for(int j=0; j<=str4[i]-'0'; j++)
		{
			if(j==str4[i]-'0')
				ret+=solve4(i+1, (s^j), 1);
			else
				ret+=solve4(i+1, (s^j), 0);
		}
	}
	else
	{
		for(int j=0; j<10; j++)
		{
			ret+=solve4(i+1, (s^j), 0);
		}
	}
	memo4[i][s][t]=true;
	return ret;
}