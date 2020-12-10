//  
//  LCA(Loweset Common Ancestor)
//
/*

    最近共通祖先をダブリングによって求める。
    計算量：前処理O(NlogN）、クエリO(logN)

    応用
    ２点間の距離　get_dist
    ２点間にある頂点aが存在しているかの判定　is_on_path

*/
#include <bits/stdc++.h>
using namespace std;
#define  rep(i,n) for (int i=0; i<(n); i++)
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using Graph = vvi;

struct LCA{
    vvi parent;
    vi dist;
    LCA(const Graph &G, int root = 0){ init(G,root); }

    void init(const Graph &G, int root = 0){
        int V = G.size();
        int k = 1;
        while((1<<k) < V) k++;
        parent.assign(k,vi(V,-1));
        dist.assign(V,-1);
        dfs(G, root, -1, 0);
        rep(i,parent.size()-1)rep(j,V){
            if(parent[i][j]!=-1) parent[i+1][j]=parent[i][parent[i][j]];
        }
    }

    void dfs(const Graph &G, int v, int p, int d){
        parent[0][v]=p;
        dist[v]=d;
        for(auto e : G[v]) if(e!=p) dfs(G,e,v,d+1);
    }

    int query(int u, int v){
        if(dist[u] < dist[v]) swap(u,v);
        int k = parent.size();
        rep(i,k){
            if((dist[u]-dist[v]) >> i & 1){
                u = parent[i][u];
            }
        }
        if(u==v) return u;
        for(int i=k-1; i>=0; i--){
            if(parent[i][u] != parent[i][v]){
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        return parent[0][u];
    }

    int get_dist(int u, int v) { 
        return dist[u] + dist[v] - 2 * dist[query(u, v)];
    }

    bool is_on_path(int u, int v, int a) {
        return get_dist(u, a) + get_dist(a, v) == get_dist(u, v);
    }
};

int main(){
    int n;
    cin >> n;
    Graph G(n);
    rep(i,n){
        int k; cin >> k;
        rep(j,k){
            int c; cin >> c;
            G[i].push_back(c);
            G[c].push_back(i);
        }
    }
    LCA lca(G);
    int q; cin >> q;
    rep(i,q){
        int u,v; cin >> u >> v;
        cout << lca.query(u,v) << endl;
    }
}
