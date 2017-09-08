#include <bits/stdc++.h>
 
using namespace std;
 
int nn, mm;
 
struct pt {
    int x, y;
};
 
struct ang {
    int a, b;
};
 
bool operator < (const ang & p, const ang & q) {
    if (p.b == 0 && q.b == 0)
        return p.a < q.a;
    return p.a * 1ll * q.b < p.b * 1ll * q.a;
}
 
long long sq (pt & a, pt & b, pt & c) {
    return a.x*1ll*(b.y-c.y) + b.x*1ll*(c.y-a.y) + c.x*1ll*(a.y-b.y);
}
 
bool solve(vector<pt> poly, vector<pt> points, int n, int m)
{
  vector<pt> p(n);
  int zero_id = 0;
    for (int i=0; i<n; ++i) {
    p[i].x = poly[i].x;
    p[i].y = poly[i].y;
        if (p[i].x < p[zero_id].x || p[i].x == p[zero_id].x && p[i].y < p[zero_id].y)
            zero_id = i;
    }
    pt zero = p[zero_id];
    rotate (p.begin(), p.begin()+zero_id, p.end());
    p.erase (p.begin());
    --n;
 
    vector<ang> a (n);
    for (int i=0; i<n; ++i) {
        a[i].a = p[i].y - zero.y;
        a[i].b = p[i].x - zero.x;
        if (a[i].a == 0)
            a[i].b = a[i].b < 0 ? -1 : 1;
    }
    for (int i = 0; i < points.size(); ++i) {
        pt q;
    q.x = points[i].x;
    q.y = points[i].y;
    bool in = false;
        if (q.x >= zero.x)
            if (q.x == zero.x && q.y == zero.y)
                in = true;
            else {
                ang my = { q.y-zero.y, q.x-zero.x };
                if (my.a == 0)
                    my.b = my.b < 0 ? -1 : 1;
                vector<ang>::iterator it = upper_bound (a.begin(), a.end(), my);
                if (it == a.end() && my.a == a[n-1].a && my.b == a[n-1].b)
                    it = a.end()-1;
                if (it != a.end() && it != a.begin()) {
                    int p1 = int (it - a.begin());
                    if (sq (p[p1], p[p1-1], q) < 0)
                        in = true;
                }
            }
    if(in == false)
        return false;
    }
  return true;
}
 
int main() {


    cin >> nn >> mm;
    vector<pt> firstpoints(nn), secondpoints(mm);
    for(int i = 0; i < nn; ++i)
        cin >> firstpoints[i].x >> firstpoints[i].y;
    for(int i = 0; i < mm; ++i)
        cin >> secondpoints[i].x >> secondpoints[i].y;

    reverse(firstpoints.begin(), firstpoints.end());
    reverse(secondpoints.begin(), secondpoints.end());
    bool a1 = solve(firstpoints, secondpoints, nn, mm);
    bool a2 = solve(secondpoints, firstpoints, mm, nn);
    if(a1 || a2)
        printf("YES\n");
    else
        printf("NO\n");
}