/**
*    author:  shu8Cream
*    created: 2024/02/03 20:48:14
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class S, S(*op)(S,S), S(*e)()>
struct segtree {
private:
    int _n;                     // 葉の数
    int size;                   // 
    vector<S> data;             // データ格納

    unsigned int bit_ceil(unsigned int n){
        unsigned int x = 1;
        while(x < (unsigned int)(n)) x*=2;
        return x;
    }

    void update(int k){ data[k] = op(data[k*2],data[k*2+1]); }

public:
    segtree(): segtree(0){}
    segtree(int n): segtree(vector<S>(n,e())) {}
    segtree(const vector<S> &v): _n(int(v.size())) {
        size = (int)bit_ceil((unsigned int)(_n));
        data = vector<S>(size*2, e());
        for(int i=0; i<_n; i++) data[size+i] = v[i];
        for(int i=size-1; i>=1; i--) update(i);
    }

    void set(int p, S x){
        assert(0<=p&&p<_n);
        p += size;
        data[p] = x;
        for(int i=p>>1; i>=1; i>>=1) update(i);
    }

    S get(int p){
        assert(0<=p&&p<_n);
        return data[p+size];
    }

    S prod(int l, int r) const {
        assert(0<=l && l<=r && r<=_n);
        S inl = e(), inr = e();
        l += size;
        r += size;
        while(l<r){
            if(l&1) inl = op(inl,data[l++]);
            l>>=1;
            if(r&1) inr = op(inr,data[--r]);
            r>>=1;
        }
        return op(inl,inr);
    }

    S all_prod() const { return data[1]; }

    void _print(int l, int r){
        assert(0<=l && l<=r && r<=_n);
        for(int i=l+size; i<r+size; i++){
            cerr << data[i] << " ";
        }
        cerr << endl;
    }
};

using S = ll;
const ll INF = 8e18;

S op(S a, S b){ return max(a,b); };
S e() { return -INF; }

void ABC339E(){
    ll n,d; cin >> n >> d;
    vector<ll> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    vector<ll> v(1000500);
    segtree<S,op,e> seg(v);
    for(int i=0; i<n; i++){
        seg.set(a[i],seg.prod(max(0LL,a[i]-d),a[i]+d+1)+1);
    }
    ll ans = seg.all_prod();
    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ABC339E();
}