//
//  トポロジカルソート（BFS・閉路検出可能）
//
/*

    頂点がトポロジカル順に帰ってくる配列のサイズが全ての頂点数と一致していれば、閉路なし。
    一致しなければ閉路が存在する。
    verify ABC216 D-Pair of Balls
    https://atcoder.jp/contests/abc216/submissions/25490365

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

template<class T> inline bool chmax(T& a, T b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) { a = b; return true; }
    return false;
}

vi topsort(vvi &to){
    vi ans;
    int n = sz(to);
    vi in(n);
    rep(i,n){
        for(auto p : to[i]) in[p]++;
    }
    queue<int> q;
    rep(i,n) if(in[i]==0) q.push(i);
    
    while(!q.empty()){
        int now = q.front(); q.pop();
        ans.push_back(now);
        for(auto p : to[now]){
            in[p]--;
            if(in[p]==0) q.push(p);
        }
    }
    return ans;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vvi to(n);
    rep(i,m){
        int k; cin >> k;
        int pre = -1;
        rep(j,k){
            int a; cin >> a;
            if(pre==-1){
                pre = a-1;
                continue;
            }
            to[pre].push_back(a-1);
            pre = a-1;
        }
    }
    vi tp = topsort(to);
    cout << (sz(tp)==n ? "Yes" : "No") << endl;
}