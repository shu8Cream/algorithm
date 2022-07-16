//
//　Least Common Multiple
//
/*

    a,bの最大公約数Gと最小公倍数Lとすると、
    GL = ab
    が成り立つ。

*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
using ll = long long;

ll gcd(ll a, ll b){
    if (b == 0) return a;
    else return gcd(b, a % b);
}

ll lcm(ll a, ll b){
    ll g = gcd(a,b);
    return a / g * b;  // オーバーフロー対策
}

int main(){
    int n,m;
    cin >> n >> m;
    cout << lcm(n,m) << endl;
}