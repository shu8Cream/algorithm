//
// １次元座標圧縮
//
/*

    NlogNで座標圧縮，区間問題などで使用
    （いもす法，イベントソート）

*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
#define all(x) (x).begin(), (x).end()
using ll = long long;
using vi = vector<int>;

template <typename T>
vector<T> compress(vector<T> &a){
    auto b = a;
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    for(auto &p:a) p = lower_bound(all(b),p) - b.begin();
    return a;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n; cin >> n;
    vi a(n);
    rep(i,n) cin >> a[i];
    vi b = compress(a);
    rep(i,n) cout << b[i] << endl;
}