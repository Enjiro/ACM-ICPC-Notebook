const double EPS = 1E-9;
const double PI = ...;
 
struct pt {
	double x, y;
	pt()  { }
	pt (double x, double y) : x(x), y(y)  { }
	pt operator- (const pt & p) const {
		return pt (x-p.x, y-p.y);
	}
};
 
double dist (const pt & a, const pt & b) {
	return sqrt ((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
 
double get_ang (const pt & a, const pt & b) {
	double ang = abs (atan2 (a.y, a.x) - atan2 (b.y, b.x));
	return min (ang, 2*PI-ang);
}
 
struct line {
	double a, b, c;
	line (const pt & p, const pt & q) {
		a = p.y - q.y;
		b = q.x - p.x;
		c = - a * p.x - b * p.y;
		double z = sqrt (a*a + b*b);
		a/=z, b/=z, c/=z;
	}
};
 
double det (double a, double b, double c, double d) {
	return a * d - b * c;
}
 
pt intersect (const line & n, const line & m) {
	double zn = det (n.a, n.b, m.a, m.b);
	return pt (
		- det (n.c, n.b, m.c, m.b) / zn,
		- det (n.a, n.c, m.a, m.c) / zn
	);
}
 
bool parallel (const line & n, const line & m) {
	return abs (det (n.a, n.b, m.a, m.b)) < EPS;
}
 
double get_h (const pt & p1, const pt & p2,
	const pt & l1, const pt & l2, const pt & r1, const pt & r2)
{
	pt q1 = intersect (line (p1, p2), line (l1, l2));
	pt q2 = intersect (line (p1, p2), line (r1, r2));
	double l = dist (q1, q2);
	double alpha = get_ang (l2 - l1, p2 - p1) / 2;
	double beta = get_ang (r2 - r1, p1 - p2) / 2;
	return l * sin(alpha) * sin(beta) / sin(alpha+beta);
}
 
struct cmp {
	bool operator() (const pair<double,int> & a, const pair<double,int> & b) const {
		if (abs (a.first - b.first) > EPS)
			return a.first < b.first;
		return a.second < b.second;
	}
};
 
int main() {
	int n;
	vector<pt> p;
	... чтение n и p ...
 
	vector<int> next (n), prev (n);
	for (int i=0; i<n; ++i) {
		next[i] = (i + 1) % n;
		prev[i] = (i - 1 + n) % n;
	}
 
	set < pair<double,int>, cmp > q;
	vector<double> h (n);
	for (int i=0; i<n; ++i) {
		h[i] = get_h (
			p[i], p[next[i]],
			p[i], p[prev[i]],
			p[next[i]], p[next[next[i]]]
		);
		q.insert (make_pair (h[i], i));
	}
 
	double last_time;
	while (q.size() > 2) {
		last_time = q.begin()->first;
		int i = q.begin()->second;
		q.erase (q.begin());
 
		next[prev[i]] = next[i];
		prev[next[i]] = prev[i];
		int nxt = next[i],   nxt1 = (nxt+1)%n,
			prv = prev[i],   prv1 = (prv+1)%n;
		if (parallel (line (p[nxt], p[nxt1]), line (p[prv], p[prv1])))
			break;
 
		q.erase (make_pair (h[nxt], nxt));
		q.erase (make_pair (h[prv], prv));
 
		h[nxt] = get_h (
			p[nxt], p[nxt1],
			p[prv1], p[prv],
			p[next[nxt]], p[(next[nxt]+1)%n]
		);
		h[prv] = get_h (
			p[prv], p[prv1],
			p[(prev[prv]+1)%n], p[prev[prv]],
			p[nxt], p[nxt1]
		);
 
		q.insert (make_pair (h[nxt], nxt));
		q.insert (make_pair (h[prv], prv));
	}
 
	cout << last_time << endl;
}