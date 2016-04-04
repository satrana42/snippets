#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
using namespace std;
const int maxn = (int)1e5+5, lg = 17;
int n, P[maxn][lg], D[maxn], S[maxn];
vector<int> e[maxn];
void dfs(int u, int p){
	P[u][0] = p;
	if(p == -1) D[u] = 0;
	else D[u] = D[p]+1;
	S[u] = 1;
	for(int i=0;i<e[u].size();i++){
		int v = e[u][i];
		if(v == p) continue;
		dfs(v,u);
		S[u] += S[v];
	}
}
void lca_table(){
	memset(P,-1,sizeof P);
	dfs(0,-1);
	for(int j=1;j<lg;j++){
		for(int i=0;i<n;i++){
			if(P[i][j-1] == -1) P[i][j] = -1;
			else P[i][j] = P[P[i][j-1]][j-1];
		}
	}
}
int parent(int u, int h){
	for(int i=lg-1;i>=0;i--)
		if(u!= -1 && h >= (1<<i)){
			u = P[u][i]; h -= (1<<i);
		}
	return u;
}
int lca(int u, int v){
	if(D[u] > D[v]) swap(u,v);
	v = parent(v,D[v]-D[u]);
	if(u == v) return u;
	for(int i=lg-1;i>=0;i--)
		if(P[u][i] != -1 && P[u][i] != P[v][i]){
			u = P[u][i]; v = P[v][i];
		}
	return P[u][0];
}
int main(){
	ios_base::sync_with_stdio(0); cin.clear();
	cin >> n;
	for(int i=0;i<n-1;i++){
		int u,v; cin >> u >> v;
		u--; v--;
		e[u].pb(v); e[v].pb(u);
	}
	lca_table();
	int m; cin >> m;
	while(m--){
		int u,v; cin >> u >> v;
		u--; v--;
		int l = lca(u,v);
	}
}