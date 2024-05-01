/**
*    author:  shu8Cream
*    created: 2024/05/01 19:18:04
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct UndoableUnionFind{
    int n;
    vector<int> par;
    vector<pair<int,int>> history;
    int group_cnt;
    UndoableUnionFind(){}
    UndoableUnionFind(int n=0): n(n), par(n, -1), group_cnt(n) {}
    int find(int x){
        if(par[x] < 0) return x;
        return find(par[x]);
    }
    bool merge(int x, int y){
        x = find(x); y = find(y);
        history.emplace_back(x,par[x]);
        history.emplace_back(y,par[y]);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x,y); //マージテク
        par[x] += par[y];
        par[y] = x;
        group_cnt--;
        return true;
    }
    bool same(int x, int y) {return find(x) == find(y);}
    int size(int x) {return -par[find(x)];}

    void undo(){
        int u = history.back().first;
        par[history.back().first] = history.back().second;
        history.pop_back();
        int v = history.back().first;
        par[history.back().first] = history.back().second;
        history.pop_back();
        if(u!=v) group_cnt++;
    }

    void snapshot() {
        while (!history.empty()) history.pop_back();
    }

    void rollback() {
        while (!history.empty()) undo();
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ll n; cin >> n;
    
    ll ans = 0;
    cout << ans << endl;
}