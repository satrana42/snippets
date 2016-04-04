#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
using namespace std;
const int maxn = 3e5+5;

int n, m, a, b, yes, tot_cmp, D[maxn], B[maxn], C[maxn], V[maxn], L[maxn], M[maxn];
vector< pair<int,int> > e[maxn], f[maxn];
queue<int> q[maxn];

// Find Bridges
int dfs_bridges(int u, int idx){
	V[u] = 1;
	int cur = D[u];
	for(int i=0;i<e[u].size();i++){
		int v = e[u][i].F, jdx = e[u][i].S;
		if(!V[v]){
			D[v] = D[u] + 1;
			cur = min(cur, dfs_bridges(v,jdx));
		}
		else if(jdx != idx) cur = min(cur, D[v]);
	}
	if(cur == D[u] && idx != -1){
		B[idx] = 1;
	}
	return cur;
}

// Construct Bridge Graph
void dfs_bg(int u, int cmp){
	q[cmp].push(u);
	while(!q[cmp].empty()){
		int v = q[cmp].front();
		q[cmp].pop(); 
		if(V[v]) continue;
		V[v] = 1; L[v] = cmp;
		for(int i=0;i<e[v].size();i++){
			int w = e[v][i].F, idx = e[v][i].S;
			if(V[w]) continue;
			if(B[idx]){
				f[cmp].pb(mp(tot_cmp,idx));
				f[tot_cmp].pb(mp(cmp,idx));
				dfs_bg(w,tot_cmp++);
			} else {
				if(C[idx]) M[cmp] = 1;
				q[cmp].push(w);
			}
		}
	}
}

// Traverse Bridge Graph
void dfs_tr(int u, int p, int bf){
	bf |= M[u];
	if(u == L[b]) yes = bf;
	for(int i=0;i<f[u].size();i++){
		int v = f[u][i].F, idx = f[u][i].S;
		if(v == p) continue;
		dfs_tr(v,u,bf | C[idx]);
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i=0;i<m;i++){
		int u, v, k; cin >> u >> v >> k;
		u--; v--; C[i] = k;
		e[u].pb(mp(v,i));
		e[v].pb(mp(u,i));
	}
	cin >> a >> b; a--; b--;

	dfs_bridges(0,-1);
	memset(V,0,sizeof V);
	dfs_bg(0,tot_cmp++);
	dfs_tr(L[a],-1,0);

	if(yes) cout << "YES\n";
	else cout << "NO\n";
	return 0;
}