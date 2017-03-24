/// David Mateus Batista <david.batista3010@gmail.com>
/// Computer Science - Federal University of Itajuba - Brazil

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define INF 0x3F3F3F3F
#define LINF 0x3F3F3F3F3F3F3F3FLL
#define DINF (double)1e+30
#define EPS (double)1e-9
#define PI (double)acos(-1.0)
#define RAD(x) (double)(x*PI)/180.0
#define PCT(x,y) (double)x*100.0/y
#define pb push_back
#define mp make_pair
#define pq priority_queue
#define F first
#define S second
#define D(x) x&(-x)
#define RESET(a,b) memset(a, b, sizeof(a))
#define DEBUG(x,y) cout << x << y << endl
#define gcd(x,y) __gcd(x, y)
#define lcm(x,y) (x*y)/gcd(x,y)
#define bitcount(x) __builtin_popcount(x)
#define llbitcount(x) __builtin_popcountll(x)

enum {North, East, South, West};
//{0, 1, 2, 3}
//{Up, Right, Down, Left}

int mi[] = {-1, 0, 1, 0, -1, 1, 1, -1};
int mj[] = {0, 1, 0, -1, 1, 1, -1, -1};

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

void init()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	cout << "[FREOPEN]" << endl;
	return;
}

int main()
{
	init();
	int x;
	scanf("%d %d", &x, &k);
	sprintf(str, "%d", x);

	//bruteforce A
	int cnt=0;
	for(int i=0; i<=x; i++)
	{
		int aux=0;
		int j=i;
		while(j)
		{
			aux+=j%10;
			j/=10;
		}
		cnt+=aux==k;
	}
	//pd x bruteforce
	n=strlen(str);
	printf("%d [%d]\n", solve(0, 0, 1), cnt);

	//bruteforce B
	int cnt2=0;
	for(int i=0; i<=x; i++)
	{
		int j=i;
		while(j)
		{
			cnt2+=j%2;
			j/=2;
		}
	}
	for(int i=0, y=x; y>0; y/=2)
		str2.pb((y%2)+'0');
	reverse(str2.begin(), str2.end());
	n2=str2.size();

	printf("%d [%d]\n", solve2(0, 0, 1), cnt2);

	//Bruteforce C
	int cnt3=0;
	for(int i=0; i<=x; i++)
	{
		int y=i;
		int aux=0;
		while(y)
		{
			aux+=y%10;
			y/=10;
		}
		cnt3+=(aux%k==0);
	}
	sprintf(str3, "%d", x);
	n3=strlen(str3);
	printf("%d [%d]\n", solve3(0, 0, 1), cnt3);


	//Bruteforce D
	int cnt4=0;
	for(int i=0; i<=x; i++)
	{
		int y=i;
		int aux=0;
		while(y)
		{
			aux^=y%10;
			y/=10;
		}
		//printf("%d\n", aux);
		cnt4+=(aux==k);
	}
	sprintf(str4, "%d", x);
	n4=strlen(str4);
	printf("%d [%d]\n", solve4(0, 0, 1), cnt4);
 	return 0;
}