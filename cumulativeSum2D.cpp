//
//  二次元累積和
//
/*

    二次元累積和の構造体
    add: 位置(x,y)を指定 0indexed, 値zを追加
    build: 累積和の作成
    query: 平面上の累積和
    verify: https://atcoder.jp/contests/abc203/tasks/abc203_d

*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
#define rrep(i,n) for (int i=(n-1); i>=0; i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) int((x).size())
using ll = long long;
using P = pair<ll,ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
const ll INF = 8e18;

template<class T> inline bool chmax(T& a, T b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) { a = b; return true; }
    return false;
}

template<class T>
struct CumulativeSum2D{
    vector<vector<T>> data;
    CumulativeSum2D(int h, int w) : data(h+1, vector<T>(w+1,0)) {}

    void add(int x, int y, T z){
        x++; y++;
        if(x>=sz(data) || y>=sz(data[0])) return;
        data[x][y]+=z;
    }

    void build(){
        for(int i=1; i<sz(data); i++){
            for(int j=1; j<sz(data[i]); j++){
                data[i][j] += data[i][j-1] + data[i-1][j] - data[i-1][j-1];
            }
        }
    }

    T query(int sx, int sy, int gx, int gy){
        gx++; gy++;
        return (data[gx][gy] - data[sx][gy] - data[gx][sy] + data[sx][sy]);
    }
};

int n,k;

bool check(ll x, vvi &a){
    CumulativeSum2D<ll> r2d(n,n);
    rep(i,n)rep(j,n){
        if(x <= a[i][j]) r2d.add(i,j,1); 
    }
    r2d.build();
    rep(i,n-k+1)rep(j,n-k+1){
        int sum = r2d.query(i,j,i+k-1,j+k-1);
        if(sum<k*k/2+1) return false;
    }
    return true;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> n >> k;
    vvi a(n, vi(n));
    rep(i,n)rep(j,n) cin >> a[i][j];
    ll ok = 0, ng = 1e10;
    while(ng-ok>1){
        ll mid = (ok+ng)/2;
        if(check(mid, a)) ok = mid;
        else ng = mid;
    }
    cout << ok << endl;
}