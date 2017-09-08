struct state {
	char p, t;
	bool pstep;
};};

vector <state> g [100] [100] [2];
// 1 = policeman coords; 2 = thief coords; 3 = 1 if policeman's step or 0 if thief's.
bool win [100] [100] [2];
bool loose [100] [100] [2];
bool used [100] [100] [2];
int degree [100] [100] [2];

void dfs (char p, char t, bool pstep) {
	used [p] [t] [pstep] = true;
	for (vector <state> :: iterator i = g [p] [t] [pstep] .begin (); i! = g [p] [t] [pstep] .end (); ++ i)
		if (! used [i-> p] [i-> t] [i-> pstep]) {
			if (loose [p] [t] [pstep])
				win [i-> p] [i-> t] [i-> pstep] = true;
			else if (--degree [i-> p] [i-> t] [i-> pstep] == 0)
				loose [i-> p] [i-> t] [i-> pstep] = true;
			else
				continue;
			dfs (i-> p, i-> t, i-> pstep);
		}
}


int main () {

	int n, m;
	cin >> n >> m;
	vector <string> a (n);
	for (int i = 0; i <n; ++ i)
		cin >> a [i];

	for (int p = 0; p <n * m; ++ p)
		for (int t = 0; t <n * m; ++ t)
			for (char pstep = 0; pstep <= 1; ++ pstep) {
				int px = p / m, py = p% m, tx = t / m, ty = t% m;
				if (a [px] [py] == '*' || a [tx] [ty] == '*') continue;
				
				bool & wwin = win [p] [t] [pstep];
				bool & lloose = loose [p] [t] [pstep];
				if (pstep)
					wwin = px == tx && py == ty, lloose =! wwin && a [tx] [ty] == 'E';
				else
					wwin = a [tx] [ty] == 'E', lloose =! wwin && px == tx && py == ty;
				if (wwin || lloose) continue;

				state st = {p, t,! pstep};
				g [p] [t] [pstep] .push_back (st);
				st.pstep = pstep! = 0;
				degree [p] [t] [pstep] = 1;
				
				const int dx [] = {-1, 0, 1, 0, -1, -1, 1, 1};
				const int dy [] = {0, 1, 0, -1, -1, 1, -1, 1};
				for (int d = 0; d <(pstep? 8: 4); ++ d) {
					int ppx = px, ppy = py, ttx = tx, tty = ty;
					if (pstep)
						ppx + = dx [d], ppy + = dy [d];
					else
						ttx + = dx [d], tty + = dy [d];
					if (ppx> = 0 && ppx <n && ppy> = 0 && ppy <m && a [ppx] [ppy]! = '*' &&
						ttx> = 0 && ttx <n && tty> = 0 && tty <m && a [ttx] [tty]! = '*')
					{
						g [ppx * m + ppy] [ttx * m + tty] [! pstep] .push_back (st);
						++ degree [p] [t] [pstep];
					}
				}
			}

	for (int p = 0; p <n * m; ++ p)
		for (int t = 0; t <n * m; ++ t)
			for (char pstep = 0; pstep <= 1; ++ pstep)
				if ((win [p] [t] [pstep] || loose [p] [t] [pstep]) &&! used [p] [t] [pstep])
					dfs (p, t, pstep! = 0);

	int p_st, t_st;
	for (int i = 0; i <n; ++ i)
		for (int j = 0; j <m; ++ j)
			if (a [i] [j] == 'C')
				p_st = i * m + j;
			else if (a [i] [j] == 'T')
				t_st = i * m + j;

	cout << (win [p_st] [t_st] [true]? "WIN": loose [p_st] [t_st] [true]? "LOSS": "DRAW");

}