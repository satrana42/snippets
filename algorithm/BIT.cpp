#include <iostream>
#include <cstring>
using namespace std;
struct bit{
	int *b,n;
	bit(int _n){
		n = _n;
		b = new int[n+1];
		memset(b,0,(n+1)*sizeof(int));
	}
	int query(int idx){
		int ans = 0;
		while(idx){
			ans += b[idx];
			idx -= idx&(-idx);
		}
		return ans;
	}
	void update(int idx,int k){
		while(idx<=n){
			b[idx] += k;
			idx += idx&(-idx);
		}
	}
};
int main(){
	bit t (100);
	t.update(1,1);
	t.update(3,1);
	t.update(4,-2);
	cout << t.query(1) << " " << t.query(2) << " " << t.query(3) << " " <<  t.query(4);
	return 0;
}
