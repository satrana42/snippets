#include <bits/stdc++.h>
using namespace std;
// Taken from http://e-maxx.ru/algo/treap
struct item {
	int key, prior;
	item * l, * r;
	item () {}
	item (int key, int prior = (rand()<<15) | rand()): 
		key (key), prior (prior), l (NULL), r (NULL) {}
};
typedef item * pitem;

void split (pitem t, int key, pitem &l, pitem &r) {
	if (!t)
		l = r = NULL;
	else if (key < t->key) // Equal elements go to right
		split (t->l, key, l, t->l), r = t;
	else
		split (t->r, key, t->r, r), l = t;
}

void insert (pitem &t, pitem it) {
	if (!t)
		t = it;
	else if (it->prior > t->prior)
		split (t, it->key, it->l, it->r), t = it;
	else
		insert (it->key < t->key ? t->l: t->r, it);
}

void merge (pitem &t, pitem l, pitem r) { 
	// Assumes all keys of left are smaller than that of right
	if (!l || !r)
		t = l ? l: r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r), t = l;
	else
		merge (r->l, l, r->l), t = r;
}

void erase (pitem &t, int key) {
	if (t->key == key)
		merge (t, t->l, t->r);
	else
		erase (key < t->key ? t->l: t->r, key);
}

void print (pitem &t) {
	if (!t) return;
	print(t->l);
	cout << t->key << " ";
	print(t->r);
}

int main() {
	srand(time(NULL));

	pitem t, l, r;

	insert(t, new item(2));
	insert(t, new item(1));
	insert(t, new item(3));
	cout << "T: "; print(t); cout << endl;

	split(t, 2, l, r);
	cout << "L: "; print(l); cout << endl;
	cout << "R: "; print(r); cout << endl;
}