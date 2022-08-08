/**
 * @file kruskal.cpp
 * @author shu8Cream
 * @brief 
 * @version 0.1
 * @date 2022-08-08
 * 
 * @verify
 * 
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
#define rrep(i,n) for (int i=(n-1); i>=0; i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
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

template<typename T=ll>
struct edge {
    int from, to;
    T cost;
};

struct UnionFind{
    vector<int> par;
    vector<map<int, int>> mp;
    UnionFind(int n=0): par(n, -1), mp(n) {}
    int find(int x){
        if(par[x] < 0) return x;
        return par[x] = find(par[x]);
    }
    bool merge(int x, int y){
        x = find(x); y = find(y);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x,y);
        for(auto p : mp[y]){
            mp[x][p.first] += p.second;
        }
        mp[y] = map<int,int>();
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    bool same(int x, int y) {return find(x) == find(y);}
    int size(int x) {return -par[find(x)];}
};

template<typename T>
T kruskal(vector<edge<T>> &edges, int v){
    sort(all(edges), [](const edge<T> &a, const edge<T> &b) {
        return a.cost < b.cost;
    });
    UnionFind uf(v);
    T res = 0;
    for(edge<T> &e : edges){
        if(uf.merge(e.to, e.from)){
            res += e.cost;
        }
    }
    return res;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int v,e; cin >> v >> e;
    vector<edge<int>> vec(e);
    rep(i,e){
        int s,t,w; cin >> s >> t >> w;
        vec[i] = {s,t,w};
    }
    int ans = kruskal(vec,v);
    cout << ans << endl;
}