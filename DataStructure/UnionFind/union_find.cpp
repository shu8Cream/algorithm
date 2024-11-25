#include <bits/stdc++.h>
using namespace std;

struct UnionFind{
    vector<int> par;
    vector<int> left;   // min element
    vector<int> right;  // max element
    UnionFind(){}
    UnionFind(int n=0): par(n, -1), left(n), right(n){
        for(int i=0; i<n; i++){
            left[i] = i;
            right[i] = i;
        }
    }
    int find(int x){
        if(par[x] < 0) return x;
        return par[x] = find(par[x]);
    }
    bool merge(int x, int y){
        x = find(x); y = find(y);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x,y); //マージテク
        par[x] += par[y];
        par[y] = x;
        left[x] = min(left[x], left[y]);
        left[y] = left[x];
        right[x] = max(right[x], right[y]);
        right[y] = right[x];
        return true;
    }
    bool same(int x, int y) {return find(x) == find(y);}
    int size(int x) {return -par[find(x)];}
    int group_min(int x) {return left[find(x)];}
    int group_max(int x) {return right[find(x)];}
};

void ABC380E(){
    int n,q; cin >> n >> q;
    UnionFind uf(n);
    int op,x,c;
    vector<long> color(n),cnt(n);
    for(int i=0;i<n;++i){
        color[i] = i;
        cnt[i] = 1;
    }
    while(q--){
        cin >> op;
        if(op==1){
            cin >> x >> c;
            x--,c--;
            x = uf.find(x);
            cnt[color[x]] -= uf.group_max(x) - uf.group_min(x) + 1;
            cnt[c] += uf.group_max(x) - uf.group_min(x) + 1;
            color[x] = c;
            long l = uf.find(max(uf.group_min(x)-1,0));
            long r = uf.find(min(uf.group_max(x)+1,n-1));
            if(color[l]==color[x]){
                uf.merge(l,x);
            }
            x = uf.find(x);
            if(color[r]==color[x]){
                uf.merge(r,x);
            }
        }
        if(op==2){
            cin >> c; c--;
            cout << cnt[c] << endl;
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ABC380E();
}