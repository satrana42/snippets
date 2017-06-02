#include <bits/stdc++.h>
using namespace std;
// Taken from http://e-maxx.ru/algo/treap
// Implicit Treap: An array that supports logarithmic add, delete 
// and lazy segment operations
// key is not stored but is the number of elements smaller than current one
// and is calculated dynamically
// Not tested (yet)
typedef struct item * pitem;
struct item {
	int prior, value, cnt; // cnt stores size of subtree
	bool rev;
	pitem l, r;
	item () {}
	item (int value, int prior = (rand()<<15) | rand()): 
		value (value), prior (prior), cnt (0), l (NULL), r (NULL) {}
};

int cnt (pitem it) {
	return it? it->cnt: 0;
}

void upd_cnt (pitem it) {
	if (it)
		it->cnt = cnt (it->l) + cnt (it->r) + 1;
}

void push (pitem it) {
	if (it && it->rev) {
		it->rev = false;
		swap (it->l, it->r);
		if (it->l) it->l->rev ^= true;
		if (it->r) it->r->rev ^= true;
	}
}

void merge (pitem &t, pitem l, pitem r) {
	push (l); // lazy propagation
	push (r);
	if (!l || !r)
		t = l ? l: r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r), t = l;
	else
		merge (r->l, l, r->l), t = r;
	upd_cnt (t); // update key value
}

void split (pitem t, pitem &l, pitem &r, int key, int add = 0) {
	if (!t)
		return void (l = r = 0);
	push (t);
	int cur_key = add + cnt (t->l); // calculate the implicit key
	if (key <= cur_key) // equal elements go to right
		split (t->l, l, t->l, key, add), r = t;
	else
		split (t->r, t->r, r, key, add + 1 + cnt (t-> l)), l = t;
	upd_cnt (t);
}

void insert (pitem &t, pitem it, int key, int add = 0) {
	if (!t)
		return void (t = it);
	push (t);
	int cur_key = add + cnt (t->l); // calculate the implicit key
	if (it->prior > t->prior)
		split (t, it->l, it->r, key), t = it;
	else
		insert (key < cur_key ? t->l: t->r, it, key, add + 1 + cnt(t->l));
	upd_cnt (t);
}

void reverse (pitem t, int l, int r) {
	pitem t1, t2, t3;
	split (t, t1, t2, l);
	split (t2, t2, t3, r-l + 1);
	t2->rev ^= true;
	merge (t, t1, t2);
	merge (t, t, t3);
}

void print(pitem &t, int add = 0) {
	if (!t) return;
	push (t);
	print(t->l, add);
	int cur_key = add + cnt(t->l);
	cout << cur_key << ":" << t->value << " ";
	print(t->r, cur_key + 1);
}

int main () {
	srand(time(NULL));

	pitem t, l, r;

	insert(t, new item(2), 0);
	insert(t, new item(1), 0);
	insert(t, new item(3), 2);
	cout << "T: "; print(t); cout << endl;

	split(t, l, r, 1);
	cout << "L: "; print(l); cout << endl;
	cout << "R: "; print(r); cout << endl;
}