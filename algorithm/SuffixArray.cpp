#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int maxn = 1e5+5, lg = 18; // ceil(log N)
char s[maxn]; int n, ln, R[lg][maxn], L[maxn]; 
// R[j][i] -> Rank (of substring of length j) starting at i
// L[i] = LCP(i,i-1), look down for lcp definition

struct suffix{
	int f, s, i;
	suffix(){}
	suffix(int _f, int _s, int _i){
		f = _f; s = _s; i = _i;
	}
	bool operator==(suffix other){
		return other.f == f && other.s == s;
	}
	bool operator<(suffix other){
		return f < other.f || (f == other.f && s < other.s);
	}
} T[maxn]; // helper array for rank updating

void SuffixArray(){
	for(int i=0;i<n;i++) R[0][i] = s[i];
	int j, len;
	for(j=1,len=1;len < 2*n;j++,len<<=1){
		for(int i=0;i<n;i++) 
			// -1 represents null at end of string
			T[i] = (i+len) < n? suffix(R[j-1][i],R[j-1][i+len],i) : suffix(R[j-1][i],-1,i);
		sort(T,T+n);
		for(int i=0;i<n;i++) 
			R[j][T[i].i] = (i > 0 && T[i-1] == T[i])? R[j][T[i-1].i] : i;
	}
	ln = j; // ln = log n
}

int LCP(int x, int y){ // LCP of xth smallest suffix and yth smallest suffix
	x = T[x].i, y = T[y].i; int ans = 0;
	for(int i=ln-1;i>=0 && x<n && y<n;i--){
		if(R[i][x] == R[i][y]) ans += (1<<i), x += (1<<i), y += (1<<i);
	}
	return ans;
}

void makeLCP(){
	L[0] = 0;
	for(int i=1;i<n;i++) L[i] = LCP(i,i-1);
}

long long uniqueSubstrings(){
	long long ans = 0;
	makeLCP();
	for(int i=0;i<n;i++){
		ans += n - T[i].i - L[i];
	}
	return ans;
}

int main(){
	// ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; scanf("%d",&t);
	while(t--){
		scanf("%s",s);
		n = strlen(s);
		SuffixArray();
		long long ans = uniqueSubstrings();
		printf("%lld\n",ans);
	}
	return 0;
}