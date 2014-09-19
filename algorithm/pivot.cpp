#include <iostream>
using namespace std;
int a[100];
int pivot(int val){
	int idx = 0;
	for(int i=0;i<10;i++){
		if(a[i] < val){
			swap(a[i],a[idx]);
			idx++;
		}
	}
	return idx;
}
int main(){
	for(int i=0;i<10;i++) a[i] = 10-i,cout<<a[i] << " ";
	cout << endl;
	int x = pivot(3);
	cout << x << " " << a[x] << endl;
	for(int i=0;i<10;i++) cout << a[i] << " ";
	cout << endl;
	x = pivot(5); 
	cout << x << " " << a[x] << endl;
	for(int i=0;i<10;i++) cout << a[i] << " ";
	cout << endl;
}