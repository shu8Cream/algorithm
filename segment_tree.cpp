//
//　Segment tree / セグメントツリー
//
/*

    セグメントツリー
    区間和・Max・Minクエリ、一点更新クエリ
    verify ABC185 F - Range Xor Query
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

template<class T>
class SegTree {
    int n;                      // 葉の数
    vector<T> data;             // データ格納
    T e;                        // 単位元かつ初期値
    function<T(T,T)> ope;       // 区間クエリの演算
    function<T(T,T)> update;    // 一点更新で使う演算

    T _query(int a, int b, int k, int l, int r) {
        if(r<=a || b<=l) return e;
        if(a<=l && r<=b) return data[k];
        else{
            T c1 = _query(a, b, 2*k+1, l, (l+r)/2);
            T c2 = _query(a, b, 2*k+2, (l+r)/2,r);
            return ope(c1,c2);
        }
    }

public:
    SegTree(size_t _n, T _e, function<T(T,T)> _ope,
            function<T(T,T)> _update)
        : e(_e), ope(_ope), update(_update) {
        n = 1;
        while(n<_n) n *= 2;
        data = vector<T>(2*n-1,e);
    }

    void change(int i, T x) {
        i += n-1;
        data[i] = update(data[i],x);
        while(i>0){
            i = (i-1)/2;
            data[i] = ope(data[i*2+1], data[i*2+2]);
        }
    }

    T query(int a, int b){
        return _query(a,b,0,0,n);
    }

    T operator[](int i) {
        return data[i+n-1];
    }
};

function<ll(ll,ll)> ope = [](ll a, ll b) { return a^b; };
function<ll(ll,ll)> update = [](ll a, ll b) { return a^b; };

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n,q; cin >> n >> q;
    SegTree<ll> st(n,0,ope,update);
    rep(i,n){
        int a; cin >> a;
        st.change(i,a);
    }
    rep(i,q){
        int t,x,y; cin >> t >> x >> y;
        if(t==1){
            st.change(x-1,y);
        }else{
            cout << st.query(x-1,y) << endl;
        }
    }
}