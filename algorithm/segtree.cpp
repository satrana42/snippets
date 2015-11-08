#include <iostream>
using namespace std;
struct segtree{
	int *m, *a, *p, n;
	segtree(int _n, int * _a){
		n = _n;
		a = _a;
		m = new int[2*n+1];
		p = new int[n];
	}
	int _init(int l,int r, int nd){
		if(l==r){
			p[l] = nd;
			return m[nd] = l;
		}
		int mid = (l+r)/2;
		int x = _init(l,mid,nd<<1);
		int y = _init(mid+1,r,(nd<<1) + 1);
		if(a[x] < a[y]) return m[nd] = x;
		else return m[nd] = y;
	}
	void init(){
		_init(0,n-1,1);
	}
	void update(int idx, int val){
		int temp = p[idx];
		a[idx] = val;
		while(temp){
			if(val > m[temp]) break;
			m[temp] = idx;
		}
	}
	int _query(int l, int r, int i, int j,int nd){
		if(l>j || r<i) return -1;
		if(i<=l && j>=r) return m[nd];
		int mid = (l+r)/2;
		int x = _query(l,mid,i,j,nd<<1);
		int y = _query(mid+1,r,i,j,(nd<<1) + 1);
		if(x==-1) return y;
		if(y==-1) return x;
		if(a[x] < a[y]) return x;
		return y; 
	}
	int query(int i, int j) {
		return _query(0,n-1,i,j,1);
	}

};
int main(){
	int a[10];
	for(int i=0;i<10;i++) a[i] = i;
	segtree s (10,a);
	s.init();
	cout << s.query(0,5) << " \n" << s.query(2,4) << endl;
	s.update(2,100);
	cout << s.query(2,4);
	return 0;
}