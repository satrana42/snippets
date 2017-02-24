#include <bits/stdc++.h>
const int mod = 1e9+7;
typedef long long ll;
using namespace std;
// inline ll mul(ll a, ll b, ll m) {
//     return ((__int128)a * b) % m;
// }
ll mul(ll a, ll b, ll c){
    ll x = 0, y=a%c;
    while(b > 0){
        if(b%2 == 1){
            x = (x+y)%c;
        }
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}
ll power(ll a, ll n, ll m) {
    ll ret = 1;
    while (n) {
        if (n&1ll) ret = mul(ret, a, m);
        a = mul(a, a, m);
        n >>= 1;
    }
    return ret;
}
bool millerRabinProbable (ll n, ll a) {
    int r = 0; ll d = n-1;
    while (d%2 == 0) {
        d >>= 1; r++;
    }
    ll x = power(a, d, n);
    if (x == 1 || x == n-1) return true;
    for (int j=0;j<r-1;j++) {
        x = mul(x, x, n);
        if (x == 1) return false;
        if (x == n-1) return true;
    }
    return false;
}
bool millerRabin (ll n) {
    if (n < 2) return false;
    if (n <= 3) return true;
    
    int a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    int k = sizeof(a)/sizeof(a[0]);

    for (int i=0;i<k;i++) {
        if (a[i] == n) return true;
        if (!millerRabinProbable (n, a[i])) {
            return false;
        }
    }
    return true;
}
bool isSquare (ll x) {
    ll r = sqrt(x);
    return (r*r == x || (r+1)*(r+1) == x);
}
int main()
{
    ll n;
    scanf("%lld", &n);
    int ans = 1;
    for (ll i=2; i <= n/i/i; i++) if (n%i == 0) {
        int pwr = 0;
        while (n%i == 0) {
            pwr++; n /= i;
        }
        int cur = pwr+1;
        ans = mul(ans, cur, mod);
    }
    if (n > 1) {
        if (millerRabin(n)) {
            int cur = 2;
            ans = mul(ans, cur, mod);
        } else if (isSquare(n)) {
            int cur = 3;
            ans = mul(ans, cur, mod);
        } else {
            int cur = 4;
            ans = mul(ans, cur, mod);
        }
    }
    printf("%d\n", ans);
    return 0;
}
