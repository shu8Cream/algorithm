//
//  木の直径(tree diameter)
//  verified: 
//
/*

    適当な頂点から一番先まで探索して、一番遠いところを新たな頂点として
    探索をすると最長距離が木の直径と等しい（BFS/DFS）

*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
#define all(x) (x).begin(), (x).end()
using ll = long long;
using P = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vi>;

template <typename T>
struct Edge { int to; T cost; };
using Graph = vector<vector<Edge<ll>>>;

template <typename T>
pair<T, int> dfs(const Graph &G, int u, int par) {
    pair<T, int> ret = make_pair((T)0, u);
    for (auto e : G[u]) {
        if (e.to == par) continue;
        auto next = dfs<T>(G, e.to, u);
        next.first += e.cost;
        ret = max(ret, next);
    }
    return ret;
}
template <typename T>
T tree_diamiter(const Graph &G) {
    pair<T, int> p = dfs<T>(G, 0, -1);
    pair<T, int> q = dfs<T>(G, p.second, -1);
    return q.first;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    Graph G(n);
    rep(i,n-1){
        int a,b; cin >> a >> b;
        a--; b--;
        G[a].push_back({b,1});
        G[b].push_back({a,1});
    }
    auto ans = tree_diamiter<ll>(G);
    cout << ans << endl;
}