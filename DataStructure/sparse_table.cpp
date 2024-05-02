/**
*    author:  shu8Cream
*    created: 2024/05/02 01:09:34
*
*    @verify https://judge.yosupo.jp/problem/staticrmq
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class S, S (*op)(S, S), S (*e)()>
struct SparseTable{
    int n;
    vector<vector<S>> table;
    SparseTable(){}
    SparseTable(vector<S> arr): n(arr.size()) {
        int lgn = 0;
        while((1<<lgn)<=n) lgn++;
        table.resize(lgn);
        table[0] = arr;
        for(int i=1;i<lgn;i++){
            assert(n-(1<<i)+1>0);
            table[i].assign(n-(1<<i)+1,e());
            for(int j=0;j+(1<<i)<=n;j++){
                table[i][j] = op(table[i-1][j],table[i-1][j+(1<<(i-1))]);
            }
        }
    }

    S prod(int l, int r) const { // [l,r)  0-indexed
        assert(0<=l && r<=n);
        if(l>=r) return e();
        int rng = r-l;
        int lg = 31 - __builtin_clz(rng);
        return op(table[lg][l], table[lg][r-(1<<lg)]);
    }

    void debug_view(){
        for(int i=0;i<table.size();i++){
            for(int j=0;j<table[i].size();j++) cerr << table[i][j] << (j-1==table[i].size()?"\n":" ");
        }
    }
};

using S = ll;
const ll INF = 8e18;

S op(S a, S b){ return max(a,b); };
S e() { return 0; }

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n,q; cin >> n >> q;
    vector<S> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    SparseTable<S,op,e> sp(a);
    for(int qi=0;qi<q;qi++){
        int l,r; cin >> l >> r;
        cout << sp.prod(l,r) << endl;
    }
}