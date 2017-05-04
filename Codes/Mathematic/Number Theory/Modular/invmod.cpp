template<typename T>T extGcd(T a, T b, T &x, T &y)
{
	if(b==0)
	{
		x=1;
		y=0;
		return a;
	}
	else
	{
		T g=extGcd(b, a%b, y, x);
		y-=a/b*x;
		return g;
	}
}

template<typename T>T invMod(T a, T m)
{
	T x, y;
	extGcd(a, m, x, y);
	return (x%m+m)%m;
}