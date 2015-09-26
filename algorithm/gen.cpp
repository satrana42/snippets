#include <iostream>
using namespace std;
int main(){
	srand(time(NULL));
	int n = 50001;
	cout << n << endl; 
	for(int i=0;i<n-1;i++){
		// cout << i << " " << 2*i+1 << "\n" << i << " " << 2*i+2 << endl;
		cout << i << " " << i+1 << endl;
	}
	for(int i=0;i<n;i++) cout << (rand()%n + 1)*6 << " ";
	cout << "\n";
	int q = 25000;
	cout << 2*q << endl;
	for(int i=0;i<q;i++) cout << "C " << rand()%n << " " <<  rand()%n << " " << (rand()%n)*4 << "\n";
	for(int i=0;i<q;i++) cout << "F " << rand()%n << " " <<  rand()%n << "\n";
}