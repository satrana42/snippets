#include <bits/stdc++.h>
using namespace std;

//Tested on SPOJ/TAXI
const int maxn = 1005, inf  = 1e9+7;
int e[maxn][maxn], from[maxn]; // Set edge capacity

int find_path(int n, int source, int sink){
	queue<int> q;
	memset(from,-1,sizeof from);
	
	q.push(source);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int i=0;i<n;i++) if(i != source && from[i] == -1 && e[u][i] != 0){
			from[i] = u;
			if(i == sink) break;
			q.push(i);
		}
		if(from[sink] != -1) break;
	}

	int u = sink, min_cost = inf;
	while(from[u] != -1){
		int v = from[u];
		min_cost = min(min_cost, e[v][u]);
		u = v;
	}
	if(min_cost >= inf) return 0;

	u = sink;
	while(from[u] != -1){
		int v = from[u];
		e[v][u] -= min_cost; e[u][v] += min_cost;
		u = v;
	}
	return min_cost;
}
int max_flow(int n, int source, int sink){
	int result = 0;
  	while(true){
  		int path_capacity = find_path(n, source, sink);
  		if(path_capacity == 0) break;
  		result += path_capacity;
  	}
  	return result;
}

int a[maxn][2], b[maxn][2];
int main(){
	ios_base::sync_with_stdio(0); cin.clear();
	int t; cin >> t;
	while(t--){
		int n, m, c, s; cin >> n >> m >> c >> s;
		for(int i=0;i<n;i++){
			cin >> a[i][0] >> a[i][1];
		}
		for(int i=0;i<m;i++){
			cin >> b[i][0] >> b[i][1];
		}
		memset(e,0,sizeof e);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				int dis = abs(a[i][0]-b[j][0]) + abs(a[i][1] - b[j][1]);
				if(dis*200 <= c*s) e[i][n+j] = 1;
			}
		for(int i=0;i<n;i++)
			e[n+m][i] = 1;
		for(int i=0;i<m;i++)
			e[n+i][n+m+1] = 1;
		int ans = max_flow(n+m+2,n+m,n+m+1);
		cout << ans << "\n";
	}
	return 0;
}