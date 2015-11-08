#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define pb push_back
#define N 50005
#define LN 16
using namespace std;
int gcd(int a,int b){
  int r;
  if(a<0) a=-a;
  if(b<0) b=-b;
  while(a){r=b; b=a; a=r%a;}
  return b;
}
vector<int> adj[N];
int val[N], st[N*6][4], qt[N*6][3], sz[N], dp[N], par[LN][N], chead[N], bpos[N], base[N];
int n, ptr, S, E, diff;

// void print_tree(int cur, int s, int e){
// 	int m = (s+e)>>1; int lc = cur<<1; int rc = lc|1;
// 	// cout << s << " " << e << ": " << st[cur][0] << " " << st[cur][1] << " " << st[cur][2] << " " << st[cur][3] << endl;
// 	// cout << s << " " << e << ": " << qt[cur][0] << " " << qt[cur][1] << " " << qt[cur][2] << endl;
// 	if(s==e-1) return;
// 	print_tree(lc,s,m); print_tree(rc,m,e); 
// }

void dfs(int cur, int prev){
	if(prev == -1) dp[cur] = 0;
	else dp[cur] = dp[prev]+1;
	sz[cur] = 1;
	par[0][cur] = prev;
	for(int i=0;i<adj[cur].size();i++){
		int u = adj[cur][i];
		if(u == prev) continue;
		dfs(u,cur);
		sz[cur] += sz[u]; 
	}
}

void hld(int cur, int prev, int hd){
	chead[cur] = hd;
	// cout << cur << " " << prev << " " << hd << " " << cid << endl;
	base[ptr] = val[cur];
	// cout << "HLD: " << ptr << " " << cur << " " << base[ptr] << endl;
	bpos[cur] = ptr++;
	int sc = -1, mx = 0;
	for(int i=0;i<adj[cur].size();i++){
		int u = adj[cur][i];
		if(u == prev) continue;
		if(sc == -1 || sz[u] > mx){
			mx = sz[u];
			sc = u;
		}
	}
	if(sc == -1) return;
	hld(sc,cur,hd);
	for(int i=0;i<adj[cur].size();i++){
		int u = adj[cur][i];
		if(u == prev || u == sc) continue;
		hld(u,cur,u);
	}
}

inline void prop(int cur, int lc, int rc){
	st[cur][1] = gcd(st[lc][1],st[rc][1]);
	st[cur][1] = gcd(st[cur][1],st[rc][0]-st[lc][2]);
	st[cur][0] = st[lc][0];
	st[cur][2] = st[rc][2];
}

inline void qprop(int cur, int lc, int rc){
	if(qt[lc][0] != -1 && qt[rc][0] != -1){
		qt[cur][1] = gcd(qt[lc][1],qt[rc][1]);
		qt[cur][1] = gcd(qt[cur][1],qt[rc][0]-qt[lc][2]);
		qt[cur][0] = qt[lc][0];
		qt[cur][2] = qt[rc][2];
	}
	else if(qt[lc][0] == -1){
		qt[cur][0] = qt[rc][0];
		qt[cur][1] = qt[rc][1];
		qt[cur][2] = qt[rc][2];
	}
	else{
		qt[cur][0] = qt[lc][0];
		qt[cur][1] = qt[lc][1];
		qt[cur][2] = qt[lc][2];
	}
}

void make_tree(int cur, int s, int e){
	if(s == e-1){
		st[cur][0] = base[s];
		st[cur][1] = 0;
		st[cur][2] = base[s];
		st[cur][3] = 0;
		// cout << "Make Tree: " << s << ": " << st[cur][0] << " " << st[cur][1] << " " << st[cur][2] << endl;
		return;
	}
	int m = (s+e)>>1; int lc = cur << 1; int rc = lc|1;
	make_tree(lc,s,m); make_tree(rc,m,e);
	prop(cur,lc,rc);
	// cout << "Make Tree: " << s << " " << e << " " << st[cur][0] << " " << st[cur][1] << " " << st[cur][2] << endl;
}

void query_tree(int cur, int s, int e){
	int m = (s+e)>>1; int lc = cur << 1; int rc = lc|1;
	if(st[cur][3]!=0){
		// cout << "Lazy Prop: " << s << " " << e << " " << S << " " << E << " " << st[cur][3] << endl;
		st[cur][0] += st[cur][3];
		st[cur][2] += st[cur][3];
		if(s!=e-1){
			st[lc][3] += st[cur][3];
			st[rc][3] += st[cur][3];
		}
		st[cur][3] = 0;
	}
	if(E <= s  || S >= e){
		qt[cur][0] = qt[cur][1] = qt[cur][2] = -1;
		return;
	}
	if(s >= S && e <= E){
		qt[cur][0] = st[cur][0];
		qt[cur][1] = st[cur][1];
		qt[cur][2] = st[cur][2];
		// cout << "Query Tree: " << s << " " << e << " " << S << " " << E << ": " << qt[cur][0] << " " << qt[cur][1] << " " << qt[cur][2] << endl;
		return;
	}
	query_tree(lc,s,m); query_tree(rc,m,e);
	prop(cur,lc,rc);
	qprop(cur,lc,rc);
	// cout << "Query Tree: " << s << " " << e << " " << S << " " << E << ": " << qt[cur][0] << " " << qt[cur][1] << " " << qt[cur][2] << endl;
}

void update_tree(int cur, int s, int e){
	int m = (s+e)>>1; int lc = cur << 1; int rc = lc|1;
	if(E <= s || S >= e) return;
	if(s >= S && e <= E){
		st[cur][3] += diff;
		// cout << "Add Lazy: " << s << " " << e << " " << S << " " << E << " " << diff << ": " << st[cur][0] << " " << st[cur][1] << " " << st[cur][2] << " " << st[cur][3] << endl;
		return;
	}
	update_tree(lc,s,m); update_tree(rc,m,e);
	// prop(cur,lc,rc);
	// cout << "Update Tree: " << s << " " << e << " " << S << " " << E << " " << diff << ": " << st[cur][0] << " " << st[cur][1] << " " << st[cur][2] << " " << st[cur][3] << endl;
}

inline void update_up(int u, int v, int d){
	int uc,vc=chead[v],hd;
	// cout << "Update: " << u << " " << v << " " << d << endl;
	while(1){
		uc = chead[u];
		if(uc == vc){
			// cout << "Update up: " << u << " " << v << endl;
			S = bpos[v]; E = bpos[u]+1; diff = d;
			update_tree(1,0,ptr);
			break;
		}
		hd = chead[u];
		// cout << "Update up: " << u << " " << hd << endl;
		S = bpos[hd]; E = bpos[u]+1; diff = d;
		update_tree(1,0,ptr);
		u = par[0][hd];
	}
	// cout << "Updated: " << endl << endl;
}

inline int query_up(int u, int v){
	int uc, vc = chead[v], hd;
	int ret = 0;
	// cout << "Query: " << u << " " << v << endl;
	while(1){
		uc = chead[u];
		if(uc == vc){
			S = bpos[v]; E = bpos[u]+1;
			query_tree(1,0,ptr);
			int cur = gcd(qt[1][0],qt[1][1]);
			ret = gcd(ret,cur);
			// print_tree(1,0,ptr);
			// cout << "Query up: " << u << " " << v << ": " << cur << " " << ret << endl << endl;
			break;
		}
		hd = chead[u];
		S = bpos[hd]; E = bpos[u]+1;
		query_tree(1,0,ptr);
		int cur = gcd(qt[1][0],qt[1][1]);
		ret = gcd(ret,cur);
		// print_tree(1,0,ptr);
		// cout << "Query up: " << u << " " << hd << ": " << cur << " " << ret << endl << endl;
		u = par[0][hd];
	}
	// cout << "Query ret: " << ret << endl << endl;
	return ret;
}

int lca(int u, int v){
	if(dp[u] < dp[v]) swap(u,v);
	int del = dp[u] - dp[v];
	for(int i=LN-1;i>=0;i--) if((del>>i)&1) u = par[i][u];
	if(u == v) return u;
	for(int i=LN-1; i>=0; i--)
	if(par[i][u] != par[i][v]) {
		u = par[i][u];
		v = par[i][v];
	}
	return par[0][u];
}

inline void update(int u, int v, int d){
	int l = lca(u,v);
	update_up(u,l,d);
	// cout << "Tree:\n"; print_tree(1,0,ptr); cout << endl;
	update_up(v,l,d);
	// cout << "Tree:\n"; print_tree(1,0,ptr); cout << endl;
	update_up(l,l,-d);
	// cout << "Tree:\n"; print_tree(1,0,ptr); cout << endl;
	// cout << "Final Update: " << u << " " << v << " " << l << " " << d << endl;
	// cout << endl;
}

inline int query(int u, int v){
	int l = lca(u,v),lq,rq;
	lq = query_up(u,l); rq = query_up(v,l);
	// cout << "Final Query: " << u << " " << v << " " << l << ": " << lq << " " << rq << endl;
	return gcd(lq,rq);
}
#define cin(n) scanf("%d",&n)
#define cout(n) printf("%d\n",n)
using namespace std;
int main(){
	// ios_base::sync_with_stdio(0);
	cin(n);
	// cout << n << endl;
	for(int i=0;i<n-1;i++){
		int x,y;
		cin(x); cin(y);
		adj[x].pb(y); adj[y].pb(x);
	}
	for(int i=0;i<n;i++){
		cin(val[i]);
	}
	// cout << "input done" << endl;
	memset(chead,-1,sizeof chead); memset(par,-1,sizeof par);
	dfs(0,-1);
	// cout << "done dfs" << endl;
	
	ptr = 0;
	hld(0,-1,0);
	// cout << "done dfs" << endl;
	make_tree(1,0,ptr);
	// cout << "done dfs" << endl << endl;
	for(int i=1;i<LN;i++)
		for(int j=0;j<n;j++)
			if(par[i-1][j] != -1){
				par[i][j] = par[i-1][par[i-1][j]];
			}
	int q; cin(q); char dum; scanf("%c",&dum);
	while(q--){
		char c; int x,y,z;
		scanf("%c",&c); cin(x); cin(y);
		if(c == 'C') cin(z);
		// cout << "Debug begins: " << endl;
		if(c == 'F') cout(query(x,y));
		else update(x,y,z);
		scanf("%c",&dum);
		// print_tree(1,0,ptr);
		// cout << "Debug ends\n---------------------------------------------------------" << endl;
	}
	return 0;
}