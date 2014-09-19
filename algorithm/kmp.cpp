#include <iostream>
#include <string>
using namespace std;
struct kmp{
	string t,p;
	int* b;
	int* m; 
	kmp(string _t, string _p){
		t = _t;
		p = _p;
		b = new int[p.length()+1];
		m = new int[t.length()];
	}
	void init(){
		int i=0,j=-1;
		b[0]=-1;
		while(i<t.length()){
			while(j>=0 && p[j] != p[i]) j=b[j];
			i++; j++;
			b[i]=j;
		}
	}
	void match(){
		int i=0,j=0;
		while(i<t.length()){
			while(j>=0 && p[j] != t[i]) j=b[j];
			i++; j++;
			m[i]=j;
			if(j==p.length()){
				cout << "Match: " << i-j << endl;
				j = b[j];
			}
		}
	}
};
int main(){
	kmp k ("seventy seven","seven");
	k.init();
	k.match();
	return 0;
}