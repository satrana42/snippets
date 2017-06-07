#include <bits/stdc++.h>
using namespace std;

// Segment Tree with Lazy Propogation
// Tested here: http://codeforces.com/contest/597/submission/14215953
const int N = 1e5+5, inf = 2e9; // N -> max size of base array
struct segtree{ //max segtree
	int n, t[4*N], d[4*N]; 
	// n -> size of base array, t[i] -> value of segtree nodes, d[i] -> lazy update
	segtree(int _n = 0){
		n = _n;
		memset(t,0,sizeof(int)*4*n); // 0 -> default value 
		memset(d,0,sizeof(int)*4*n);
	}
	void push(int k, int l, int r) { //k -> node number, [l,r] -> lazy update interval
	    t[k] += d[k];
	    if(l < r) {
	        d[k<<1] += d[k];
	        d[k<<1|1] += d[k];
	    }
	    d[k] = 0;
	}
	int _update(int k, int l, int r, int x, int y, int v) { 
	// k -> node number, [l,r] -> segtree interval, [x,y] -> update interval, v -> increment value 
	    push(k, l, r);
	    if(l > y || r < x) {
	        return t[k];
	    }
	    if(l >= x && r <= y) {
	        d[k] += v; // lazy update operation
	        return d[k] + t[k];
	    }
	    int mid = (l+r)>>1;
	    // replace max with your function
	    return t[k] = max(_update(k<<1, l, mid, x, y, v), _update(k<<1|1, mid+1, r, x, y, v)); 
	}
	void update(int l, int r, int v){ // [l,r] -> update interval, v -> increment value
		_update(1, 0, n-1, l, r, v);
	}
	int _query(int k, int l, int r, int x, int y) {
	 // k -> node number, [l,r] -> segtree interval, [x,y] -> query interval
	    push(k, l, r);
	    if(l > y || r < x) {
	        return -inf; // return identity here
	    }
	    if(l >= x && r <= y) {
	        return t[k];
	    }
	    int mid = (l+r)>>1;
	    // replace max with your function
	    return max(_query(k<<1, l, mid, x, y), _query(k<<1|1, mid+1, r, x, y)); 
	}
	int query(int l, int r){ // [l,r] -> query interval
		return _query(1,0,n-1,l,r);
	}
};
int main(){
	int a[10];
	for(int i=0;i<10;i++) a[i] = i;
	segtree s(10);
	for(int i=0;i<10;i++) s.update(i,i,a[i]);
	cout << s.query(0,5) << endl << s.query(2,4) << endl;
	s.update(2,2,100);
	cout << s.query(2,4) << endl;
	return 0;
}