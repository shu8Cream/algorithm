//
//  LCS(Longest Common Subsequence)
//
/*

    二次元配列のDP、文字列aの長さ、文字列bの長さの積のサイズが必要

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

int LCS[2020][2020];

void init(){
    rep(i,2020)rep(j,2020){
        LCS[i][j]=0;
    }
}

int solve(string a, string b){
    if(sz(b) > sz(a)) swap(a,b);
    int A = sz(a), B = sz(b);
    for(int i=1; i<=A; i++){
        for(int j=1; j<=B; j++){
            if(a[i-1]==b[j-1]) LCS[i][j] = LCS[i-1][j-1]+1;
            else LCS[i][j] = max(LCS[i][j-1], LCS[i-1][j]);
        }
    }
    return LCS[A][B];
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n; cin >> n;
    rep(i,n){
        string a,b; cin >> a >> b;
        init();
        cout << solve(a,b) << endl;
    }
}