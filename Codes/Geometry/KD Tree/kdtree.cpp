struct point
{ 
    ll x, y, z;
    point(ll x=0, ll y=0, ll z=0): x(x), y(y), z(z) {}
    point operator-(point q) { return point(x-q.x, y-q.y, z-q.z); }
    ll operator*(point q) { return x*q.x + y*q.y + z*q.z; }
};
typedef vector<point> polygon;

struct KDTreeNode
{
    point p;
    int level;
    KDTreeNode *below, *above;
	
    KDTreeNode (const point& q, int levl)
    {
        p = q;
        level = levl;
        below = above = 0;
    }
    ~KDTreeNode() { delete below, above; }
	
    int diff (const point& pt)
    {
        switch (level)
        {
        case 0: return pt.x - p.x;
        case 1: return pt.y - p.y;
        case 2: return pt.z - p.z;
        } 
        return 0;
    }
    ll distSq (point& q) { return (p-q)*(p-q); }

    int rangeCount (point& pt, ll K)
    {
        int count = (distSq(pt) < K*K) ? 1 : 0;
        int d = diff(pt);
        if (-d <= K && above != 0)
            count += above->rangeCount(pt, K);
        if (d <= K && below != 0)
            count += below->rangeCount(pt, K);
        return count;
    }
};

class KDTree
{
public:
    polygon P;
    KDTreeNode *root;
    int dimention;
    KDTree() {}
    KDTree(polygon &poly, int D)
    {
        P = poly;
        dimention = D;
        root = 0;
        build();
    }
    ~KDTree() { delete root; }
		
    //count the number of pairs that has a distance less than K
    ll countPairs(ll K)
    {
        ll count = 0;
        f(i, 0, P.size())
            count += root->rangeCount(P[i], K) - 1;
        return count;
    }
		
protected:
    void build()
    {
        random_shuffle(all(P));
        f(i, 0, P.size()) {
            root = insert(root, P[i], -1);
        }
    }
    KDTreeNode *insert(KDTreeNode* t, const point& pt, int parentLevel)
    {
        if (t == 0)
        {
            t = new KDTreeNode (pt, (parentLevel+1) % dimention);
            return t;
        }
        else
        {
            int d = t->diff(pt);
            if (d <= 0) t->below = insert (t->below, pt, t->level);
            else t->above = insert (t->above, pt, t->level);
        }
        return t;
    }
};

int main()
{
    int n, k;
    point e;
    polygon p;
    while (cin >> n >> k && n+k)
    {
        p.clear();
        f(i, 0, n)
        {
            cin >> e.x >> e.y >> e.z;
            p.pb(e);
        }
        KDTree tree(p, 3);
        cout << tree.countPairs(k) / 2LL << endl;
    }
    return 0;
}
