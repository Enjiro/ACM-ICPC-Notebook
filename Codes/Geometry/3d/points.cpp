#define vetor point

// FORMULAS.
//  vetores a,b; a*b = a.mod()*b.mod()*cos( angulo entre a e b) =>
// a*b = |a|*|b|*cos(t)
//  vetores a,b; (a^b).mod() = a.mod()*b.mod()*sin( angulo entre a e b)

inline int cmp(ld x, ld y = 0, ld tol = eps)
{
	return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
struct point
{
	ld x, y, z;
	point(ld x = 0, ld y = 0, ld z = 0): x(x), y(y), z(z) {}
	point operator +(point q) { return point(x + q.x, y + q.y, z + q.z); }
	point operator -(point q) { return point(x - q.x, y - q.y, z - q.z); }
	point operator *(ld t) { return point(x * t, y * t, z * t); }
	point operator /(ld t) { return point(x / t, y / t, z / t); }
	point operator ^(point q) { 
		return point(y*q.z - z*q.y, z*q.x - x*q.z, x*q.y - y*q.x); }
	ld operator *(point q) { return x * q.x + y * q.y + z * q.z; }
	ld mod() { return sqrt(x * x + y * y + z * z); }
	ld mod2() { return x * x + y * y + z * z; }
	point projecao(vetor u) { return (*this) * ((*this)*u) / ((*this)*(*this)); } 	
	
	int cmp(point q) const
	{
		if (int t = ::cmp(x, q.x)) return t;
		if (int t = ::cmp(y, q.y)) return t;		
		return ::cmp(z, q.z);
	}
	bool operator ==(point q) const { return cmp(q) == 0; }
	bool operator !=(point q) const { return cmp(q) != 0; }
	bool operator < (point q) const { return cmp(q) < 0; }
};

// RETAS, SEMIRETAS, SEGMENTOS E TRIANGULOS
struct reta
{
	point a, b;//  <--a---b--->
	reta(point A=point(0,0,0), point B=point(0,0,0)): a(A), b(B) { }
	
	//verifica se o ponto p esta na reta ab
	bool belongs(point p)
	{
		return cmp(((a-p)^(b-p)).mod()) == 0;
	}
};
struct semireta
{
	point a, b; //  |a---b--->
	semireta(point A=point(0,0,0), point B=point(0,0,0)): a(A), b(B) { }
};
struct segmento
{
	point a, b; //  |a---b|
	segmento(point A=point(0,0,0), point B=point(0,0,0)): a(A), b(B) { }
	bool between(point p) {
		return cmp(((a-p)^(b-p)).mod()) == 0 && cmp((a-p) * (b-p)) <= 0;
	}
};
struct triangulo
{
	point a, b, c;
	triangulo(point A, point B, point C): a(A), b(B), c(C) { }
	ld area() { return 0.5*((b-a)^(c-a)).mod(); }
	
	//retorna o ponto que eh a projecao de p no plano abc
	point projecao(point p)
	{
		vetor w = (b-a)^(c-a);
		return p - w.projecao(p-a);
	}
	//verifica se p esta dentro de abc 
	// se retornar true, entao a,b,c,p sao coplanares
	bool inside(point p)
	{ 
		return cmp(((p-a)^(b-a)).mod() + 
					((p-b)^(c-b)).mod() + 
					((p-c)^(a-c)).mod() - 
					((b-a)^(c-a)).mod()) == 0;
	}
};

//Produto misto 
ld produto_misto(point p, point q, point r)
{
	return (p^q)*r;
}
//Volume do tetraedro pqrs
ld volume(point p, point q, point r, point s)
{
	return fabs(produto_misto(q-p, r-p, s-p)) / 6.0;
}

// DISTANCIA ENTRE OBJETOS GEOMETRICOS
ld distancia(point p, reta r)
{
	vetor v = r.b-r.a, w = p-r.a;
	return (v^w).mod() / v.mod();
}
ld distancia(point p, semireta s)
{
	vetor v = s.b-s.a, w = p-s.a;
	if (cmp(v*w) <= 0) return (p-s.a).mod();
	return (v^w).mod() / v.mod();
}
ld distancia(point p, segmento s)
{
	point proj = s.a + (s.b-s.a).projecao(p-s.a);
	if (segmento(s.a,s.b).between(proj))
		return (p-proj).mod();
	return min((p-s.a).mod(), (p-s.b).mod());
}
ld distancia(point p, triangulo T)
{
	point proj = T.projecao(p);
	if (T.inside(proj)) return (p-proj).mod();
	return min(	distancia(p, segmento(T.a, T.b)), 
				min(distancia(p, segmento(T.b, T.c)), 
					distancia(p, segmento(T.c, T.a))));
}
ld distancia(reta r, reta s)
{
	vetor u = r.b-r.a, v = s.b-s.a, w = s.a-r.a;
	ld a = u*u, b = u*v, c = v*v, d = u*w, e = v*w;
	ld D = a*c - b*b, sc, tc;
	if (D < eps)
	{
		sc = 0;
		tc = (b > c) ? d/b : e/c;
	}
	else
	{
		sc = (b*e - c*d) / D;
		tc = (a*e - b*d) / D;
	}
	vetor dP = w + (u * sc) - (v * tc);
	return dP.mod();
}
ld distancia(segmento X, segmento Y)
{
	point p = X.a, q = X.b;
	point r = Y.a, s = Y.b;
	if (p == q) return distancia(p, Y);
	if (r == s) return distancia(r, X);
	if (cmp(((p-q)^(s-r)).mod()) == 0) 
		return min( min(distancia(p,Y),distancia(q,Y)), 
					min(distancia(p,Y),distancia(q,Y)));
	vetor v = q-p, u = s-r, t = (r-p);
	ld b = ((t*v)*(v*u) - (t*u)*(v*v)) / ((u*u)*(v*v) - (u*v)*(v*u));
	ld a = (b*(u*v) + t*v) / (v*v);
	if (cmp(a) >= 0 && cmp(a,1.0) <= 0 && cmp(b) >= 0 && cmp(b,1.0) <= 0)
		return ((p+v*a) - (r+u*b)).mod();
	point ini = ((cmp(a) < 0)?p:q);
	point fim = ((cmp(b) < 0)?r:s);
	return (ini-fim).mod();
}

//Calcula o centro da esfera circunscrita de uma piramide triangular
point circumsphere(point p, point q, point r, point s)
{
	point a = q-p, b = r-p, c = s-p;
	return p + ((a^b)*c.mod2() + (c^a)*b.mod2() + (b^c)*a.mod2()) / (a*(b^c)*2);
}

//Calcula o circuncentro de um triangulo no espaco
point circumcenter(point p, point q, point r)
{
	point a = (q-p)^((q-p)^(r-p)), b = (r-p)^((q-p)^(r-p)); ld t;
	if (fabs(a.x) < eps) t = (r.x-q.x)/2/b.x;
	else if (fabs(a.y) < eps) t = (r.y-q.y)/2/b.y;
	else if (fabs(a.z) < eps) t = (r.z-q.z)/2/b.z;	
	else
	{
		t = a.x*(r.y-q.y) - a.y*(r.x-q.x);
		t = t / (2*a.y*b.x - 2*a.x*b.y);
	}
	return (p+q)/2 + a*t;
}

//Verifica se T[a], T[b], T[c] eh face do convex hull
//OBS.: Cuidade com mais de 3 pontos coplanares
bool ishullface(vector <point> &T, int a, int b, int c)
{//TODO testar
	int n = (int)T.size(), pos = 0, neg = 0;
	for (int i = 0; i < n; i++)
	{
		ld pm = produto_misto(T[b]-T[a], T[c]-T[a], T[i]-T[a]);
		if (cmp(pm) < 0) neg++;
		if (cmp(pm) > 0) pos++;
	}
	return (neg*pos == 0);
}
