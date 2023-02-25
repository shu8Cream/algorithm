/**
*    author:  shu8Cream
*    created: 29.12.2022 20:27:17
**/

#include <bits/stdc++.h>
using namespace std;
#define overload3(a,b,c,d,...) d
#define rep1(i,n) for (int i=0; i<(n); i++)
#define rep2(i,a,n) for (int i=(a); i<(n); i++)
#define rep(...) overload3(__VA_ARGS__, rep2, rep1)(__VA_ARGS__)
#define rrep1(i,n) for (int i=(n-1); i>=0; i--)
#define rrep2(i,a,n) for (int i=(n-1); i>=(a); i--)
#define rrep(...) overload3(__VA_ARGS__, rrep2, rrep1)(__VA_ARGS__)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) int((x).size())
#define pcnt __builtin_popcountll
using ll = long long;
using P = pair<ll,ll>;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
using vi = vc<ll>;
using vvi = vv<ll>;
const int INF = 1e9;
const ll LINF = 8e18;
template<typename T>istream& operator>>(istream&i,vc<T>&v){rep(j,sz(v))i>>v[j];return i;}
template<typename T>string join(const T&v,const string& d=""){stringstream s;rep(i,sz(v))(i?s<<d:s)<<v[i];return s.str();}
template<typename T>ostream& operator<<(ostream&o,const vc<T>&v){if(sz(v))o<<join(v," ");return o;}
template<typename T1,typename T2>istream& operator>>(istream&i,pair<T1,T2>&v){return i>>v.first>>v.second;}
template<typename T1,typename T2>ostream& operator<<(ostream&o,const pair<T1,T2>&v){return o<<v.first<<","<<v.second;}
template<class T> inline bool chmax(T& a, T b) {if(a<b) { a=b;return true; } return false;}
template<class T> inline bool chmin(T& a, T b) {if(a>b) { a=b;return true; } return false;}

template <class T> string to_string(T s);
template <class S, class T> string to_string(pair<S, T> p);
string to_string(char c) { return string(1, c); }
string to_string(string s) { return s; }
string to_string(const char s[]) { return string(s); }

template <class T>
string to_string(T v) {
    if (v.empty()) return "{}";
    string ret = "{";
    for (auto x : v) ret += to_string(x) + ",";
    ret.back() = '}';
    return ret;
}
template <class S, class T>
string to_string(pair<S, T> p) {
    return "{" + to_string(p.first) + ":" + to_string(p.second) + "}";
}

void debug_out() { cout << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cout << to_string(H) << " ";
    debug_out(T...);
}

#ifdef _DEBUG
#define debug(...) debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

template<typename S, S (*op)(S, S), S (*e)()>
struct DynamicSegTree {
public:
    DynamicSegTree(ll n): n(n),root(nullptr) {}
    void set(ll pos, S x) { set(root,0,n,pos,x); }
    S get(ll pos) { return get(root,0,n,pos); }
    S prod(ll l, ll r) { return prod(root,0,n,l,r); }

private:
    struct node {
        ll pos;
        S val, sum;
        node *left;
        node *right;
        node(ll pos, S val)
            : pos(pos), val(val), sum(val), left(nullptr), right(nullptr) {}
        void update(){
            sum = op(op(left?left->sum:e(),val),right?right->sum:e());
        }
    };
    ll n;
    node *root;

    // 0-indexed, [l,r)
    void set(node *&t, ll l, ll r, ll pos, S x){
        if(t==nullptr) t = new node(pos,x); // 単位元で初期化
        if(pos==t->pos){
            t->val = x; // 一点更新
            t->update();
            return;
        }
        ll mid = (l + r)>>1;
        if(pos<mid){
            if(t->pos < pos) { swap(t->pos,pos); swap(t->val,x); }
            set(t->left,l,mid,pos,x);
        }else{
            if(pos < t->pos) { swap(t->pos,pos); swap(t->val,x); }
            set(t->right,mid,r,pos,x);
        }

        // 葉以外のノードを更新
        // ここの演算は区間クエリに依存
        t->update();
    }

    S get(node *&t, ll l, ll r, ll pos){
        if(t==nullptr) return e(); // 単位元を返す
        if(pos==t->pos) return t->val;
        ll mid = (l + r)>>1;
        if(pos<mid) return get(t->left,l,mid,pos);
        else return get(t->right,mid,r,pos);
    }

    S prod(node *&t, ll sl, ll sr, ll l, ll r){
        if(t==nullptr) return e(); // 単位元を返す
        if(sr<=l || r<=sl) return e(); // 単位元を返す
        if(l<=sl && sr<=r) return t->sum;
        ll mid = (sl + sr)>>1;
        S res = prod(t->left,sl,mid,l,r);
        if(l<=t->pos && t->pos < r) res = op(res,t->val);
        return op(res, prod(t->right,mid,sr,l,r));
    }
};

using ld = long double;
struct F { ld a, b; };
F op(F t, F r) { return {t.a*r.a, r.a*t.b + r.b}; }
F e() { return {1.0, 0.0}; }

// // RangeSum / point update
// using S = ll;
// S op(S a, S b) { return a+b; }
// S e() { return 0; }

void ARC008D(){
    ll n,m; cin >> n >> m;
    DynamicSegTree<F,op,e> st(n);
    ll p; ld a,b;
    ld mx = 1, mn = 1;
    rep(i,m){
        cin >> p >> a >> b; p--;
        st.set(p,{a,b});
        F res = st.prod(0,n);
        chmax(mx,res.a+res.b);
        chmin(mn,res.a+res.b);
    }
    cout << mn << "\n";
    cout << mx << "\n";
}

// void YUKI789(){
//     DynamicSegTree<S,op,e> st(1000000000);
//     int q; cin >> q;
//     int op,x,l,r; ll y;
//     ll ans = 0;
//     for(;q--;){
//         cin >> op;
//         if(op==0){
//             cin >> x >> y;
//             ll v = st.get(x);
//             st.set(x,v+y);
//             debug("set", v+y);
//         }else{
//             cin >> l >> r;
//             ans += st.prod(l,r+1);
//             debug("ans", ans);
//         }
//     }
//     cout << ans << endl;
// }

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    // YUKI789();
    ARC008D();
}
