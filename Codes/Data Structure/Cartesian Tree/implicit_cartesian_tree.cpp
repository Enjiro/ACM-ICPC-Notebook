//srand(time(NULL))
int vrand()
{
	return abs(rand()<<(rand()%31));
}

struct node
{
	//basic treap: x=key, y=priority key, c=tree count;
	int x, y, c;
	//treap operations: v=max(x), lazy=lazy value of propagation, rev=reversed
	int v, lazy, rev;

	node *L, *R;
	node(){};
	node(int _x)
	{
		x=_x, y=vrand();
		L=R=NULL;
		v=x;
		lazy=0;
		rev=0;
	}
};

//updating functions
int get_cnt(node *root)
{
	return root?root->c:0;
}

void upd_cnt(node *root)
{
	if(root)
		root->c=1+get_cnt(root->L)+get_cnt(root->R);
}

void push(node *&root)
{
	if(root && root->rev)
	{
		root->rev=0;
		swap(root->L, root->R);
		if(root->L)
			root->L->rev^=1;
		if(root->R)
			root->R->rev^=1;
	}
}

void propagate(node *&root)
{
	if(root)
	{
		if(!root->lazy)
			return;
		int lazy=root->lazy;
		root->x+=lazy;

		if(root->L)
			root->L->lazy=lazy;
		if(root->R)
			root->R->lazy=lazy;
		root->lazy=0;
	}
}

int get_max(node *root)
{
	return root?root->v:-INF;
}

void upd_max(node *root)
{
	if(root)
		root->v=max(root->x, max(get_max(root->L), get_max(root->R)));
}

inline void update(node *root)
{
	propagate(root);
	upd_cnt(root);
	upd_max(root);
}

void merge(node *&root, node *L, node *R)
{
	push(L);
	push(R);
	if(!L || !R)
		root=L?L:R;
	else if(L->y > R->y)
		merge(L->R, L->R, R), root=L;
	else 
		merge(R->L, L, R->L), root=R;
	update(root);
}

void split(node *root, node *&L, node *&R, int x, int add=0)
{
	if(!root)
		return void(L=R=NULL);
	push(root);
	int ix=add+get_cnt(root->L); //implicit key
	if(x<=ix)
		split(root->L, L, root->L, x, add), R=root;
	else
		split(root->R, root->R, R, x, add+1+get_cnt(root->L)), L=root;
	update(root);
}

//insert function
void insert(node *&root, int pos, int x)//(insert x at position pos)
{
	node *R1, *R2;
	split(root, R1, R2, pos);
	merge(R1, R1, new node(x));
	merge(root, R1, R2);
}

//erase value x
void erase_x(node *&root, int x)
{
	if(!root)
		return;
	if(root->x==x)
		merge(root, root->L, root->R);
	else
		erase_x(x < root->x? root->L:root->R, x);
	update(root);
}

//erase kth value
void erase_kth(node *&root, int x)
{
	if(!root)
		return;
	int Lc=get_cnt(root->L);
	if(x-Lc-1==0)
		merge(root, root->L, root->R);
	else if(x>Lc)
		erase_kth(root->R, x-Lc-1);
	else
		erase_kth(root->L, x);
	update(root);
}

//add x to [l,r]
void paint(node *&root, int l, int r, int x)
{
	node *R1, *R2, *R3;
	split(root, R1, R2, l);
	split(R2, R2, R3, r-l+1);
	R2->lazy=x;
	propagate(R2);

	merge(root, R1, R2);
	merge(root, root, R3);
}

//max range query [l,r]
int rquery(node *&root, int l, int r)
{
	node *R1, *R2, *R3;
	split(root, R1, R2, l);
	split(R2, R2, R3, r-l+1);
	int ret=R2->v;
	merge(root, R1, R2);
	merge(root, root, R3);
	return ret;
}

void reverse(node *&root, int l, int r)//reverse elements [l, r]
{
	node *R1, *R2, *R3;
	split(root, R1, R2, l);
	split(R2, R2, R3, r-l+1);
	R2->rev^=1;
	merge(root, R1, R2);
	merge(root, root, R3);
}

//output functions
int poscnt=0;
void output_all(node *root)
{
	if(!root)
		return;
	update(root);
	push(root);
	output_all(root->L);
	printf("[%d] %d\n", poscnt++, root->x);
	output_all(root->R);
}

int output_kth(node *root, int x)
{
	if(!root)
		return -1;
	update(root);
	push(root);
	int Lc=get_cnt(root->L);
	if(x-Lc-1==0)
		return root->x;
	if(x>Lc)
		return output_kth(root->R, x-Lc-1);
	else
		return output_kth(root->L, x);
}