#include <bits/stdc++.h>
using namespace std;
// Based on http://e-maxx.ru/algo/treap
// Tested on http://codeforces.com/contest/809/problem/D
struct item {
	int key, prior, add; 
	item * l, * r;
	item () {}
	item (int key, int prior = (rand()<<15) | rand()): 
		key (key), prior (prior), add(0), l (NULL), r (NULL) {}
};
typedef item * pitem;

void push (pitem it) {
	if (it && it->add != 0) {
		it->key += it->add;
		if (it->l) it->l->add += it->add;
		if (it->r) it->r->add += it->add;
		it->add = 0;
	}
}

void split (pitem t, int key, pitem &l, pitem &r) {
	push(t);
	if (!t)
		l = r = NULL;
	else if (key <= t->key)
		split (t->l, key, l, t->l), r = t;
	else
		split (t->r, key, t->r, r), l = t;
}

void insert (pitem &t, pitem it) { // Singleton it
	push(t);
	if (!t)
		t = it;
	else if (it->prior > t->prior)
		split (t, it->key, it->l, it->r), t = it;
	else
		insert (it->key < t->key ? t->l: t->r, it);
}

void merge (pitem &t, pitem l, pitem r) { 
	// Assumes all keys of left are smaller than that of right
	push(l); push(r);
	if (!l || !r)
		t = l ? l: r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r), t = l;
	else
		merge (r->l, l, r->l), t = r;
}

void erase (pitem &t, int key) {
	if(!t) return;
	push(t);
	if (t->key == key)
		merge (t, t->l, t->r);
	else
		erase (key < t->key ? t->l: t->r, key);
}

void print (pitem &t) {
	if (!t) return;
	push(t);
	print(t->l);
	cout << t->key << " ";
	print(t->r);
}

const int inf = 1e9;
int findBegin (pitem &t) {
	push(t);
	if (t->l) return findBegin(t->l);
	return t->key;
}

int findMax(pitem &t) {
	if (!t) return 0;
	push(t);
	return findMax(t->l) + (t->key <= inf ? 1 : 0) + findMax(t->r);
}
pitem t, l, m, r, tmp;

int main() {
	srand(time(NULL));
	int n; cin >> n;
	t = new item(0);
	for (int i=1;i<=n;i++) merge(t, t, new item(inf+i));
	for (int i=0;i<n;i++) {
		int a, b; cin >> a >> b;
		split(t, a, l, r);
		split(r, b, m, r);
		if (m) m->add++;
		int mn = findBegin(r);
		split(r, mn+1, tmp, r);
		merge(t, l, new item(a));
		merge(t, t, m);
		merge(t, t, r);
	}
	int ans = findMax(t) - 1;
	cout << ans << endl;
}