//bpsw(n) returns if n is prime
#define gcd(x, y) __gcd(x, y)
ll jacobi(ll a, ll b)
{
	if(a==0 || a==1)
		return a;
	if(a<0)
	{
		if((b&2)==0)
			return jacobi(-a, b);
		return -jacobi(-a, b);
	}
	ll a1=a, e=0;
	while((a1&1)==0)
		a1>>=1, e++;
	ll s;
	if((e&1)==0 || (b&7)==1 || (b&7)==7)
		s=1;
	else
		s=-1;
	if((b&3)==3 && (a1&3)==3)
		s=-s;
	if(a1==1)
		return s;
	return s*jacobi(b%a1, a1);
}

bool bpsw(ll n)
{
	if((ll)sqrt(n+0.0)*(ll)sqrt(n+0.0)==n)
		return false;
	ll dd=5;
	while(1)
	{
		ll g=gcd(n, abs(dd));
		if(1<g && g<n)
			return false;
		if(jacobi(dd, n)==-1)
			break;
		dd=dd<0?-dd+2:-dd-2;
	}
	ll p=1, q=(p*p-dd)/4;
	ll d=n+1, s=0;
	while((d&1)==0)
		s++, d>>=1;
	ll u=1, v=p, u2m=1, v2m=p, qm=q, qm2=q*2, qkd=q;
	for(ll mask=2; mask<=d; mask<<=1)
	{
		u2m=(u2m*v2m)%n;
		v2m=(v2m*v2m)%n;
		while(v2m<qm2)
			v2m+=n;
		v2m-=qm2;
		qm=(qm*qm)%n;
		qm2=qm*2;
		if(d&mask)
		{
			ll t1=(u2m*v)%n, t2=(v2m*u)%n;
			ll t3=(v2m*v)%n, t4=(((u2m*u)%n)*dd)%n;
			u=t1+t2;
			if(u&1)
				u+=n;
			u=(u>>1)%n;
			v=(t3+t4);
			if(v&1)
				v+=n;
			v=(v>>1)%n;
			qkd=(qkd*qm)%n;
		}
	}
	if(u==0 || v==0)
		return true;
	ll qkd2=qkd*2;
	for(ll r=1; r<s; r++)
	{
		v=(v*v)%n-qkd2;
		v+=v<0?n:0;
		v+=v<0?n:0;
		v-=v>=n?n:0;
		v-=v>=n?n:0;
		if(v==0)
			return true;
		if(r<s-1)
		{
			qkd=(qkd*1LL*qkd)%n;
			qkd2=qkd*2;
		}
	}
	return false;
}