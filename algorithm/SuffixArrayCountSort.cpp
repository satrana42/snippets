#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 100010                         // second approach: O(n log n)
char T[MAX_N];                   // the input string, up to 100K characters
int n, ln;                                        // the length of input string
int RA[MAX_N], tempRA[MAX_N], R[20][MAX_N];        // rank array and temporary rank array
int SA[MAX_N], tempSA[MAX_N];    // suffix array and temporary suffix array
int c[MAX_N];                                    // for counting/radix sort


void countingSort(int k) {                                          // O(n)
  int i, sum, maxi = max(300, n+1);   // up to 255 ASCII chars or length of n
  memset(c, 0, sizeof c);                          // clear frequency table
  for (i = 0; i < n; i++)       // count the frequency of each integer rank
    c[i + k < n ? RA[i + k] : 0]++;
  for (i = sum = 0; i < maxi; i++) {
    int t = c[i]; c[i] = sum; sum += t;
  }
  for (i = 0; i < n; i++)          // shuffle the suffix array if necessary
    tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
  for (i = 0; i < n; i++)                     // update the suffix array SA
    SA[i] = tempSA[i];
}

void constructSA() {         // this version can go up to 100000 characters
  int i, j, k, r;
  for (i = 0; i < n; i++) R[0][i] = RA[i] = T[i];                 // initial rankings
  for (i = 0; i < n; i++) SA[i] = i;     // initial SA: {0, 1, 2, ..., n-1}
  for (k = 1, j = 1; k < 2*n; k <<= 1, j++) {       // repeat sorting process log n times
    countingSort(k);  // actually radix sort: sort based on the second item
    countingSort(0);          // then (stable) sort based on the first item
    tempRA[SA[0]] = r = 0;             // re-ranking; start from rank r = 0
    for (i = 1; i < n; i++)                    // compare adjacent suffixes
      tempRA[SA[i]] = // if same pair => same rank r; otherwise, increase r
      (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
    for (i = 0; i < n; i++)                     // update the rank array RA
      R[j][i] = RA[i] = tempRA[i];
    if (RA[SA[n-1]] == n-1) break;               // nice optimization trick
	}
	ln = j;
}

int L[MAX_N];
int LCP(int x, int y){ // LCP of xth smallest suffix and yth smallest suffix
	x = SA[x], y = SA[y]; int ans = 0;
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
		ans += n - SA[i] - L[i];
	}
	return ans-n; //Strings including '$'
}

int main(){
	int t; scanf("%d",&t);
	while(t--){
		scanf("%s",T); 
		n = strlen(T); n++;
		// T[n++] = '$';
		constructSA();
		long long ans = uniqueSubstrings();
		printf("%lld\n",ans);
	}
}