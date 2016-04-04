#include <bits/stdc++.h>

/*Ordered Set starts*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define T int
#define ordered_set tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>


void testOrderedSet(){
	ordered_set s;
	s.insert(0); s.insert(2);
	cout << s.order_of_key(0) << " " << s.order_of_key(2) << "\n";
	cout << *s.find_by_order(0) << " " << *s.find_by_order(1) << "\n";
}
/*Ordered Set ends*/

/*Comparison Class begins*/
struct Cmp{
    bool operator()(int a, int b){
        return a < b;
    }
};
void testComparisonClass(){
	set<int,Cmp> S; priority_queue<int, vector<int>, Cmp> Q;
}
/*Comparision Class ends*/

/*Useful macros start*/
#define FORIT(i, m) for (__typeof((m).begin()) i=(m).begin(); i!=(m).end(); ++i)
#define ALL(x) x.begin(), x.end()
#define UNIQUE(c) (c).resize( unique( ALL(c) ) - (c).begin() )
/*Useful macros end*/

/*Debug macros start*/
#define DEBUG true
#define D(x) if(DEBUG) cout << __LINE__ <<" "<< #x " = " << (x) << endl;
#define D2(x,y) if(DEBUG) cout << __LINE__ <<" "<< #x " = " << (x) \
     <<", " << #y " = " << (y) << endl;
/*Debug macros end*/

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	testOrderedSet();
	return 0;
}