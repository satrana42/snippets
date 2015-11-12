#include <bits/stdc++.h>
using namespace std;

// Iterative Segment Tree
// Tutorial: http://codeforces.com/blog/entry/18051
// Tested here: http://codeforces.com/contest/597/submission/14216671
const int N = 1e5+5; // N -> max size of base array
struct segtree{ //max segtree
	int n, t[2*N]; // n -> size of base array, t[i] -> value of segtree nodes, d[i] -> lazy update
	segtree(int _n = 0){
		n = _n;
		memset(t,0,sizeof(int)*2*n); // 0 -> default value 
	}
	void update(int i, int v){ // i -> update index, v -> increment value
  		for (t[i += n] += v; i > 1; i >>= 1) t[i>>1] = t[i] + t[i^1];
	}
	int query(int l, int r){ // [l,r] -> query interval
		r++; // [l,r) -> query interval
		int res = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) res += t[l++];
			if (r&1) res += t[--r];
		}
		return res;
	}
};
int main(){
	int a[10];
	for(int i=0;i<10;i++) a[i] = i;
	segtree s(10);
	for(int i=0;i<10;i++) s.update(i,a[i]);
	for(int i=0;i<10;i++) cout << s.query(i,i) << " ";
	cout << endl;
	cout << s.query(0,5) << endl << s.query(2,4) << endl;
	s.update(2,100);
	cout << s.query(2,4) << endl;
	return 0;
}