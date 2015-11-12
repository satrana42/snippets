#include <iostream>
using namespace std;
int a[100];
int bs(int val){
	int l=0,r=99,m;
	while(l<=r){
		m = l + (r-l)/2;
		if(a[m] == val) return m;
		else if(a[m] < val) l =m+1;
		else r = m-1; 
	}
	return -1;
}
int lb(int val){
	int l=0,r=99,m;
	while(l<r){
		m = l +(r-l)/2;
		if(a[m] < val) l = m+1;
		else r = m;
	}
	return (a[l]>=val)?l:-1;
}
int ub(int val){
	int l=0,r=99,m;
	while(l<r){
		m = l + (r-l)/2;
		if(a[m] <= val) l = m+1;
		else r = m;
	}
	return (a[l]>val)?l:-1;
}

int main(){
	for(int i=0;i<100;i++) a[i] = 2*i;
	cout << bs(50) << " \n" << lb(50) << " \n" << lb(51) << " \n" << ub(50) << " \n" << ub(51);
	return 0;
}