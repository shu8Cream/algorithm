//
//　約数列挙
//
/*

    与えられた値に対してソートされた約数配列を返す
    60の時 {1,2,3,4,5,6,10,12,15,20,30,60}

*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
using ll = long long;

vector<ll> divisor(ll n) {
    vector<ll> ret;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) ret.push_back(n / i);
        }
    }
    sort(ret.begin(), ret.end()); // 昇順に並べる
    return ret;
}

int main(){
    int n;
    cin >> n;
    vector<ll> m = divisor(n);

    for (auto div : m){
        cout << div << endl;
    }
}