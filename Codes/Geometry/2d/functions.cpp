double abs(point p) { return hypot(p.x, p.y); }
double arg(point p) { return atan2(p.y, p.x); }

inline int ccw(point p, point q, point r)
{
	return cmp((p - r) % (q - r));
}

//Projeta o vetor v sobre o vetor u (cuidado precisao)
point proj(point v, point u)
{
	return u*((u*v) / (u*u));
}

//\angle(p,q,r)| e o menor angulo entre os vetores u(p-q) e v(r-q)
// p->q->r virar pra esquerda => angle(p,q,r) < 0
inline double angle(point p, point q, point r)
{
	point u = p - q, v = r - q;
	return atan2(u % v, u * v);
}

//Decide se q esta sobre o segmento fechado pr.
bool between(point p, point q, point r)
{
	return ccw(p, q, r) == 0 && cmp((p - q) * (r - q)) <= 0;
}

//Decide se os segmentos fechados pq e rs tem pontos em comum
bool seg_intersect(point p, point q, point r, point s)
{
	point A = q - p, B = s - r, C = r - p, D = s - q;
	int a = cmp(A % C) + 2 * cmp(A % D);
	int b = cmp(B % C) + 2 * cmp(B % D);
	if (a == 3 || a == -3 || b == 3 || b == -3) return false;
	if (a || b || p == r || p == s || q == r || q == s) return true;
	int t = (p < r) + (p < s) + (q < r) + (q < s);
	return t != 0 && t != 4;
}

// Calcula a distancia do ponto r ao segmento pq.
double seg_distance(point p, point q, point r)
{
	point A = r - q, B = r - p, C = q - p;
	double a = A * A, b = B * B, c = C * C;
	if (cmp(b, a + c) >= 0) return sqrt(a);
	else if (cmp(a, b + c) >= 0) return sqrt(b);
	else return fabs(A % B) / sqrt(c);
}

// Classifica o ponto p em relacao ao poligono T.
// Retorna 0, -1 ou 1 dependendo se p esta no exterior, na fronteira
// ou no interior de T, respectivamente.
int in_poly(point p, polygon& T) {
	double a = 0; int N = T.size();
	for (int i = 0; i < N; i++) {
		if (between(T[i], p, T[(i+1) % N])) return -1;
		a += angle(T[i], p, T[(i+1) % N]);
	}
	return cmp(a) != 0;
}

//Encontra o ponto de intersecao das retas pq e rs.
point line_intersect(point p, point q, point r, point s)
{
	point a = q - p, b = s - r, c = point(p % q, r % s);
	return point(point(a.x, b.x) % c, point(a.y, b.y) % c) / (a % b);
}

// Calcula a area orientada do poligono T.
// Se o poligono P estiver em setido anti-horario, poly_area(P) > 0,
// e <0 caso contrario
double poly_area(polygon& T)
{
	double s = 0; int n = T.size();
	for (int i = 0; i < n; i++)
		s += T[i] % T[(i+1) % n];
	return s / 2;
}

//Calcula o incentro de um triangulo
point incenter(point p, point q, point r)
{
	double a = (p-q).mod(), b = (p-r).mod(), c = (q-r).mod();
	return (r*a + q*b + p*c) / (a + b + c);
}

//Centro de massa de um poligono
point centro_massa(polygon p)
{
	double x=0., y=0., area = poly_area(p);
	p.push_back(p[0]);
	for (int i = 0; i < p.size()-1; i++) {
		x += (p[i].x + p[i+1].x) * (p[i] % p[i+1]);
		y += (p[i].y + p[i+1].y) * (p[i] % p[i+1]);
	}
	return point(x/(6*area), y/(6*area));
}
