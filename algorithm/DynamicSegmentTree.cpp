// Dynamic segment tree for large range where you create nodes dynamically
// Tested on http://codeforces.com/contest/803/problem/G
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
using namespace std;
const int N = 1e5 + 5, LG = 18, inf = 1e9 + 7;

int n, k, b[N], splay[N][LG];

void pre () {
	for (int j = 0; j < LG; j++) {
		for (int i = 1; i <= n; i++) {
			if (j == 0) splay[i][0] = b[i];
			else {
				splay[i][j] = splay[i][j-1];
				if (i + (1<<(j-1)) <= n) 
					splay[i][j] = min(splay[i][j], splay[i + (1<<(j-1))][j-1]);
			}
		}
	}
}

int splay_helper (int l, int r) {
	int pw = 1, lg = 0;
	while (pw * 2 <= r - l + 1) pw <<= 1, lg++;
	int ret = min(splay[l][lg], splay[r-pw+1][lg]);
	return ret;
}

int splay_query (int l, int r) {
	int ret;
	if (r - l + 1 >= n) ret = splay_helper(1, n);
	else {
		l = ((l-1) % n) + 1, r = ((r-1) % n) + 1;
		if (r < l) ret = min(splay_helper(l, n), splay_helper(1, r));
		else ret = splay_helper(l, r);
	}
	return ret;
}

struct node {
	int x, y, set, mn;
	node *l, *r;
	node (int x, int y, int mn): x(x), y(y), set(0), mn(mn), l(0), r(0) {} 
} *root; 

void push (node *cur) {
	if (cur->set) {
		int m = (cur->x + cur->y) / 2;
		if (!cur->l) {
			cur->l = new node(cur->x, m, cur->set);
		}
		cur->l->set = cur->set; 
		if (!cur->r) {
			cur->r = new node(m + 1, cur->y, cur->set);
		}
		cur->r->set = cur->set; 
		cur->mn = cur->set;
		cur->set = 0;
	}
}

int query (node* cur, int l, int r) {
	int ret; push (cur);
	if (r < l || r < cur->x || cur->y < l) return inf;
	else if (l <= cur->x && cur->y <= r) {
		ret = cur->mn;
	}
	else {
		int m = (cur->x + cur->y)/2;
		if (!cur->l) cur->l = new node(cur->x, m, splay_query (cur->x, m));
		if (!cur->r) cur->r = new node(m + 1, cur->y, splay_query (m + 1, cur->y));
		ret = min (query(cur->l, l, r), query (cur->r, l, r));
	}
	return ret;
}

int update (node* cur, int l, int r, int val) {
	int ret; push (cur);
	if (r < l || r < cur->x || cur->y < l) ret = cur->mn;
	else if (l <= cur->x && cur->y <= r) ret = cur->set = val;
	else {
		int m = (cur->x + cur->y)/2;
		if (!cur->l) cur->l = new node(cur->x, m, splay_query (cur->x, m));
		if (!cur->r) cur->r = new node(m + 1, cur->y, splay_query (m + 1, cur->y));
		ret = cur->mn = min (update (cur->l, l, r, val), update (cur->r, l, r, val));
	}
	return ret;
}

int main () {
	scanf ("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) scanf ("%d", &b[i]);
	pre ();
	root = new node (1, n*k, splay_query (1, n));
	int q; scanf ("%d", &q); 
	while (q--) {
		int t, l, r; scanf ("%d %d %d", &t, &l, &r);
		if (t == 2) printf ("%d\n", query (root, l, r));
		else {
			int x; scanf ("%d", &x);
			update (root, l, r, x);
		}
	}
	return 0;
}