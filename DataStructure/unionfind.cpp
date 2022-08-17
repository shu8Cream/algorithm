/**
 * @file unionfind.cpp
 * @author shu8Cream
 * @brief 
 * @version 0.1
 * @date 2022-07-29
 * 
 * @verify
 * 
 * @details マージテク（データ構造をマージする一般的なテク） O(NlogN^2)
 *          連結成分の個数はsetで全頂点の親を探索して、setのサイズ
 * 
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
using ll = long long;
using P = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using Graph = vvi;

struct UnionFind{
    vector<int> par;
    // vector<map<int, int>> mp;
    UnionFind(){}
    UnionFind(int n=0): par(n, -1), mp(n) {}
    int find(int x){
        if(par[x] < 0) return x;
        return par[x] = find(par[x]);
    }
    bool merge(int x, int y){
        x = find(x); y = find(y);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x,y); //マージテク
        // for(auto p : mp[y]){
        //     mp[x][p.first] += p.second;
        // }
        // mp[y] = map<int,int>(); //メモリの解放
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    bool same(int x, int y) {return find(x) == find(y);}
    int size(int x) {return -par[find(x)];}
};

int main(){
    int n,q;
    cin >> n >> q;
    UnionFind uf(n);
    rep(_,q){
        int t,u,v;
        cin >> t >> u >> v;
        if(t){
            if(uf.same(u,v)) cout << 1 << endl;
            else cout << 0 << endl;
        }else{
            uf.merge(u,v);
        }
    }
}