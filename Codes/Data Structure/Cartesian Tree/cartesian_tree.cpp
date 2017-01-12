//srand(time(NULL))
int vrand()
{
	return abs(rand()<<(rand()%31));
}

struct node
{
	//x=key, y=priority key, c=tree count
	int x, y, c;
	node *L, *R;
	node(){};
	node(int _x)
	{
		x=_x, y=vrand(), c=0;
		L=R=NULL;
	}
};

int cnt(node *root)
{
	return root?root->c:0;
}

void upd_cnt(node *root)
{
	if(root)
		root->c=1+cnt(root->L)+cnt(root->R);
}

void split(node *root, int x, node *&L, node *&R)
{
	if(!root)
		L=R=NULL;
	else if(x < root->x)
		split(root->L, x, L, root->L), R=root;
	else
		split(root->R, x, root->R, R), L=root;
	upd_cnt(root);
}

void insert(node *&root, node *it)
{
	if(!root)
		root=it;
	else if(it->y > root->y)
		split(root, it->x, it->L, it->R), root=it;
	else
		insert(it->x < root->x? root->L:root->R, it);
	upd_cnt(root);
}

void merge(node *&root, node *L, node *R)
{
	if(!L || !R)
		root=L?L:R;
	else if(L->y > R->y)
		merge(L->R, L->R, R), root=L;
	else
		merge(R->L, L, R->L), root=R;
	upd_cnt(root);
}

void erase(node *&root, int x)
{
	if(root->x==x)
		merge(root, root->L, root->R);
	else
		erase(x < root->x? root->L:root->R, x);
	upd_cnt(root);
}

node *unite(node *L, node *R)
{
	if(!L || !R)
		return L?L:R;
	if(L->y < R->y)
		swap(L, R);
	node *Lt, *Rt;
	split(R, L->x, Lt, Rt);
	L->L=unite(L->L, Lt);
	L->R=unite(L->R, Rt);
	return L;
}

int find(node *root, int x)
{
	if(!root)
		return 0;
	if(root->x==x)
		return 1;
	if(x > root->x)
		return find(root->R, x);
	else
		return find(root->L, x);
}

int findkth(node *root, int x)
{
	if(!root)
		return -1;
	int Lc=cnt(root->L);
	if(x-Lc-1==0)
		return root->x;
	if(x>Lc)
		return findkth(root->R, x-Lc-1);
	else
		return findkth(root->L, x);
}
