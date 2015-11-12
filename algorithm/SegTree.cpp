#include <bits/stdc++.h>
using namespace std;

// Segment Tree with Lazy Propogation
// Tested here: http://codeforces.com/contest/597/submission/14216114
const int N = 1e5+5, inf = 2e9; // N -> max size of base array
struct segtree{ //max segtree
	int n, t[4*N]; // n -> size of base array, t[i] -> value of segtree nodes, d[i] -> lazy update
	segtree(int _n = 0){
		n = _n;
		memset(t,0,sizeof(int)*4*n); // 0 -> default value 
	}
	int _update(int k, int l, int r, int x, int v) { // k -> node number, [l,r] -> segtree interval, x -> update index, v -> increment value 
	    if(l > x || r < x) {
	        return t[k];
	    }
	    if(l == x && r == x) {
	        t[k] += v; // update operation
	        return t[k];
	    }
	    int mid = (l+r)>>1;
	    return t[k] = max(_update(k<<1, l, mid, x, v), _update(k<<1|1, mid+1, r, x, v)); // replace max with your function
	}
	void update(int i, int v){ // i -> update index, v -> increment value
		_update(1, 0, n-1, i, v);
	}
	int _query(int k, int l, int r, int x, int y) { // k -> node number, [l,r] -> segtree interval, [x,y] -> query interval
	    if(l > y || r < x) {
	        return -inf; // return identity here
	    }
	    if(l >= x && r <= y) {
	        return t[k];
	    }
	    int mid = (l+r)>>1;
	    return max(_query(k<<1, l, mid, x, y), _query(k<<1|1, mid+1, r, x, y)); // replace max with your function
	}
	int query(int l, int r){ // [l,r] -> query interval
		return _query(1,0,n-1,l,r);
	}
};
int main(){
	int a[10];
	for(int i=0;i<10;i++) a[i] = i;
	segtree s(10);
	for(int i=0;i<10;i++) s.update(i,a[i]);
	cout << s.query(0,5) << endl << s.query(2,4) << endl;
	s.update(2,100);
	cout << s.query(2,4) << endl;
	return 0;
}