// Tested at http://codeforces.com/contest/813/problem/E
// Taken from http://codeforces.com/contest/813/submission/27594314
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, SZ = 5e6 + 6;


struct data {
    int cnt;
    int left;
    int right;
    data() {
    	cnt = 0;
    	left = 0;
    	right = 0;
    }
} st[SZ];

int root[N], cur;

inline int newnode(int val3 , int left , int right) {
	++cur;
	st[cur].cnt = val3;
	st[cur].left = left;
	st[cur].right = right;
	return cur;
}

void insert(int &curnode , int prenode , int l , int r , int idx , int val) {
	if (idx < l || idx > r) return;
	if(l == r){
		curnode = newnode(st[prenode].cnt + val , 0 , 0);
		return;
	}
	int mid = l + r >> 1;
	if(idx <= mid){
		curnode = newnode(st[prenode].cnt + val , 0 , st[prenode].right);
		insert(st[curnode].left , st[prenode].left , l , mid , idx , val);
	}
	else{
		curnode = newnode(st[prenode].cnt + val , st[prenode].left , 0);
		insert(st[curnode].right , st[prenode].right , mid + 1 , r , idx , val);
	}
}

int query(int l , int r , int rnode , int lnode , int ql , int qr) {
	if(l > qr || r < ql || ql > qr){
		return 0;
	}
	if(l >= ql && r <= qr){
		return st[rnode].cnt - st[lnode].cnt;
	}
	int mid = l + r >> 1;
	return query(l , mid , st[rnode].left , st[lnode].left , ql , qr) + query(mid + 1 , r , st[rnode].right , st[lnode].right , ql , qr);
}

int n, k, a[N], r[N];
vector<int> pos[N];

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		pos[a[i]].pb(i);
	}
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < pos[i].size(); j++) {
			if (j + k < pos[i].size()) r[pos[i][j]] = pos[i][j+k];
			else r[pos[i][j]] = -1;
		}
	}
	for (int i = 1; i <= n; i++) {
		insert(root[i], root[i-1], 1, n, i, 1);
		if (r[i] != -1) insert(root[i], root[i], 1, n, r[i], -1);
	}
	int q, ans = 0; scanf ("%d", &q);
	while (q--) {
		int l, r; scanf("%d %d", &l, &r);
		l = (l + ans)%n + 1;
		r = (r + ans)%n + 1;
		if (l > r) swap (l, r);
		ans = query (1, n, root[r], root[l-1], l, r);
		printf ("%d\n", ans);
	}
	return 0;
}