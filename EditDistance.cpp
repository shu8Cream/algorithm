//
//  編集距離（Levenshtein Distance）
//
/*
 
    二次元配列DP、文字列の長さ同士の積のサイズ必要

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

void debug_out() { cout << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
cout << H << " ";
debug_out(T...);
}

#ifdef _DEBUG
#define debug(...) debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

int dp[2020][2020];

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    string a,b; cin >> a >> b;
    rep(i,sz(a)+1) dp[i][0] = i;
    rep(i,sz(b)+1) dp[0][i] = i;
    for(int i=1; i<sz(a)+1; i++){
        for(int j=1; j<sz(b)+1; j++){
            int c = (a[i-1] == b[j-1] ? 0 : 1);
            dp[i][j] = min({dp[i-1][j]+1, dp[i][j-1]+1, dp[i-1][j-1]+c});
        }
    }
    cout << dp[sz(a)][sz(b)] << endl;
}