#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
const int maxn = 1e6+5;
int n, m, a[maxn], ans, M[maxn]; // m -> sqrt(n)
struct query{
	int i, l, r, ans;
} b[maxn];
bool cmp1(query x, query y){
	return mp(x.l/m,x.r) < mp(y.l/m,y.r);
}
bool cmp2(query x, query y){
	return x.i < y.i;
}
void add(int i){
	M[a[i]]++;
	if(M[a[i]] == 1) ans++;
}
void remove(int i){
	M[a[i]]--;
	if(M[a[i]] == 0) ans--;
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n; m = sqrt(n);
	for(int i=0;i<n;i++) cin >> a[i];
	int q; cin >> q;
	for(int i=0;i<q;i++){
		cin >> b[i].l >> b[i].r;  b[i].l--; b[i].r--;
		b[i].i = i;
	}
	sort(b,b+q,cmp1);
	int l = 0, r = 0; M[a[0]] = 1; ans = 1;
	for(int i=0;i<q;i++){
		while(l < b[i].l){
			remove(l); l++;
		}
		while(l > b[i].l){
			l--; add(l);
		}
		while(r > b[i].r){
			remove(r); r--;
		}
		while(r < b[i].r){
			r++; add(r);
		}
		b[i].ans = ans;
	}
	sort(b,b+q,cmp2);
	for(int i=0;i<q;i++) cout << b[i].ans << "\n";
}