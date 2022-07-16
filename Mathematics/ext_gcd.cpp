//
//　拡張gcd
//
/*

    拡張ユークリッドの互除法
    ax + by = gcd(a,b) の解である、x,yも出力する
    ax = b (mod N) の解xを求める手法でもある

*/
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
using ll = long long;

// return x,y,g  s.t.  ax + by = gcd(a,b)
tuple<ll, ll, ll> extgcd(ll a, ll b){
    if(a == 0) return {0, 1, b};
    ll x,y,g;
    tie(x,y,g) = extgcd(b%a, a);
    return {y-b/a*x, x, g};
}

int main() {
    /* debug
    ll x, y, g;
    const int MOD = 1e9+7;
    for(int a=1; a<=100; a++){
        tie(x,y,g) = extgcd(a,MOD);
        if(((a * x % MOD) +MOD)%MOD == 1) cout << "OK" << endl;
        else cout << "NG" << x << " " << y << " " << g << endl;
    }
    */

    int a, b;
    cin >> a >> b;
    ll x,y,g;
    tie(x,y,g) = extgcd(a,b);
    printf("%d %d %d\n", x,y,g);
}