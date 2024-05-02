/**
*    author:  shu8Cream
*    created: 2024/05/01 21:18:49
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class S, S (*op)(S, S), S (*e)()>
struct SparseTable{ // O(NlogN) for precalculation, O(1) per query
    int n;
    vector<vector<S>> table;
    SparseTable(){}
    SparseTable(const vector<S> &arr): n(arr.size()) {
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

template <class S, S (*op)(S, S), S (*e)()>
struct SparseTable2D { // O(HWlogHlogW) for precalculation, O(1) per query
    int h,w;
    vector<vector<SparseTable<S,op,e>>> data;
    SparseTable2D(){}
    SparseTable2D(const vector<vector<S>> &mat): h(mat.size()),w(mat.size()?mat[0].size():0){
        int lgh = 0;
        while((1<<lgh)<=h) lgh++;
        data.resize(lgh);
        for(auto v:mat) data[0].emplace_back(SparseTable<S,op,e>(v));
        for(int ih=1; ih<lgh; ih++){
            for(int i=0; i+(1<<ih)<=h; i++){
                vector<S> v(w);
                for(int j=0; j<w; j++){
                    v[j] = op(data[ih-1][i].data[0][j], data[ih-1][i+(1<<(ih-1))].data[0][j]);
                }
                data[ih].emplace_back(SparseTable<S,op,e>(v));
            }
        }
    }

    S prod(int xl, int xr, int yl, int yr) const {
        assert(0<=xl && xr<=h && 0<=yl && yr<=w);
        if(xl>=xr) return e();
        int rng = xr-xl;
        int lg = 31 - __builtin_clz(rng);
        return op(data[lg][xl].prod(yl,yr), data[lg][xr-(1<<lg)].prod(yl,yr));
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
    ll n; cin >> n;
    vector<vector<ll>> a(n,vector<ll>(n));
    SparseTable2D<S,op,e>sp(a);
    
    ll ans = 0;
    cout << ans << endl;
}