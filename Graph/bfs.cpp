//
//  BFS（幅優先探索）基本ver.
//
/*

    基本バージョン
    関数バージョン追加
    経路復元追加　20211107
        直前のノードを持つ配列prevを利用する

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

vi bfs(int s, vvi &to){
    int n = sz(to);
    vi dist(n, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int nv : to[v]) {
            if (dist[nv] != -1) continue;
            dist[nv] = dist[v] + 1;
            q.push(nv);
        }
    }
    return dist;
}

int main() {
    int n, m; cin >> n >> m;

    vvi G(n);
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    vi dist(n, -1);
    vi prev(n, -1);
    queue<int> q;
    dist[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int nv : G[v]) {
            if (dist[nv] != -1) continue;
            dist[nv] = dist[v] + 1;
            prev[nv] = v;
            q.push(nv);
        }
    }

    auto a = bfs(0,G);
    for (int v = 0; v < n; ++v) cout << v << ": " << a[v] << endl;

    // 最短経路の経路復元、curにゴールを入れる
    int cur = 5, start = 0; 
    vi res;
    while(cur!=start){
        res.push_back(cur);
        cur = prev[cur];
    }
    res.push_back(start);
    reverse(all(res));
    for(auto p : res) cout << p << " ";
    cout << endl;
}