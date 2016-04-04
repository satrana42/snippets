#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 1e5+5;
struct bit{
	int b[maxn],n;
	bit(int _n){
		n = _n;
		memset(b,0,(n)*sizeof(int));
	}
	int query(int idx){
		idx++;
		int ans = 0;
		while(idx){
			ans += b[idx];
			idx -= idx&(-idx);
		}
		return ans;
	}
	void update(int idx,int k){
		idx++;
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
