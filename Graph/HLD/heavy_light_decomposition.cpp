/**
*    author:  shu8Cream
*    created: 20.03.2023 23:12:18
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

// stable sort
template <typename T>
vc<int> argsort(const vc<T> &A) {
    vc<int> ids(sz(A));
    iota(all(ids), 0);
    sort(all(ids),
        [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });
    return ids;
}

// A[I[0]], A[I[1]], ...
template <typename T>
vc<T> rearrange(const vc<T> &A, const vc<int> &I) {
    vc<T> B(sz(I));
    rep(i, sz(I)) B[i] = A[I[i]];
    return B;
}

template <typename T, typename U>
vc<T> cumsum(vc<U> &A, int off = 1) {
    vc<T> B(sz(A) + 1);
    rep(i, sz(A)) B[i + 1] = B[i] + A[i];
    if (off == 0) B.erase(B.begin());
    return B;
}

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

/*
    size_:  部分木のサイズ
    in:     最初に通った時刻
    out:    最後に通った時刻
    par:    自身の親
    dep:    根からの深さ
    head:   pathの先頭
    rev:    逆辺
*/
struct HLDecomposition {
    int n;
    vv<int> G;
    vc<int> size_,in,out,par,dep,head,rev;
    HLDecomposition(){}
    HLDecomposition(int n):
        n(n),G(n),size_(n,1),in(n),out(n),
        par(n,-1),dep(n),head(n),rev(n){}

    // u,v: 0-indexed
    void add_edge(int u, int v){
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void build(){
        dfs_sz(0);
        int time = 0;
        dfs_hld(0,time);
    }

    // u: 0-indexed, uからk個登る
    // int la(int u, int k){}

    int lca(int u, int v){
        while(1){
            if(in[u]>in[v]) swap(u,v);
            if(head[u]==head[v]) return u;
            v = par[head[v]];
        }
    }

    int dist(int u, int v){
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    // 問題によって書き換え
    template<typename F>
    void for_each_node(int u, int v, const F& f){
        while(1){
            if(in[u]>in[v]) swap(u,v);
            f(max(in[head[v]],in[u]),in[v]+1);
            if(head[u]!=head[v]) v = par[head[v]];
            else break;
        }
    }

    template<typename F>
    void for_each_edge(int u, int v, const F& f){
        while(1){
            if(in[u]>in[v]) swap(u,v);
            if(head[u]!=head[v]){
                f(in[head[v]],in[v]+1);
                v = par[head[v]];
            }else{
                if(u!=v) f(in[u]+1,in[v]+1);
                break;
            }
        }
    }

private:
    void dfs_sz(int v){
        for(int &nv:G[v]){
            if(nv==par[v]) continue;
            par[nv] = v;
            dep[nv] = dep[v]+1;
            dfs_sz(nv);
            size_[v]+=size_[nv];
            if(size_[nv]>size_[G[v][0]]) swap(nv,G[v][0]);
        }
    }

    void dfs_hld(int v, int &time){
        in[v] = time++;
        rev[in[v]] = v;
        for(int &nv:G[v]){
            if(nv==par[v]) continue;
            head[nv] = (nv==G[v][0]?head[v]:nv);
            dfs_hld(nv,time);
        }
        out[v] = time;
    }
};

template<typename T>
struct BIT{
public:
    int n; vector<T> a;
    BIT(int n_):n(n_),a(n_+1,0){}

    void add(int idx, T x){
        idx++;
        assert(0<idx && idx<=n && "Index error");
        for(int i=idx; i<=n; i+=i&(-i)) a[i]+=x;
    }

    T sum(int idx){
        T res = 0;
        idx++;
        assert(0<=idx && idx<=n && "Index error");
        if(idx==0) return 0;
        for(int i=idx; i>0; i-=(i&-i)) res+=a[i];
        return res;
    }

    T sum(int l, int r){
        if(l==0) return sum(r-1);
        return sum(r-1)-sum(l-1);
    }
};

void Vertex_Add_Path_Sum(){
    int n,q; cin >> n >> q;
    vi a(n); cin >> a;
    HLDecomposition hld(n);
    int op,p,u,v; ll x;
    rep(i,n-1){
        cin >> u >> v;
        hld.add_edge(u,v);
    }
    hld.build();

    BIT<ll> bit(n);
    rep(i,n) bit.add(hld.in[i],a[i]);

    rep(qi,q){
        cin >> op;
        if(op==0){
            cin >> p >> x;
            bit.add(hld.in[p],x);
        }else{
            cin >> u >> v;
            ll ans = 0;
            auto f = [&](int l,int r){
                ans+=bit.sum(l,r);
            };
            hld.for_each_node(u,v,f);
            cout << ans << "\n";
        }
    }
    cout << flush;
}

void Lowest_Common_Ancestor(){
    int n,q; cin >> n >> q;
    HLDecomposition hld(n);
    rep(i,1,n){
        int p; cin >> p;
        hld.add_edge(i,p);
    }
    hld.build();
    rep(qi,q){
        int u,v; cin >> u >> v;
        cout << hld.lca(u,v) << endl;
    }
}

void AOJ_LCA(){
    int n; cin >> n;
    HLDecomposition hld(n);
    int k,c;
    rep(i,n){
        cin >> k;
        rep(j,k){
            cin >> c;
            hld.add_edge(i,c);
        }
    }
    hld.build();
    int q; cin >> q;
    rep(qi,q){
        int u,v; cin >> u >> v;
        cout << hld.lca(u,v) << endl;
    }
}

void ABC014_D(){
    int n; cin >> n;
    HLDecomposition hld(n);
    rep(i,n-1){
        int x,y; cin >> x >> y;
        hld.add_edge(x-1,y-1); 
    }
    hld.build();
    int q; cin >> q;
    rep(qi,q){
        int u,v; cin >> u >> v;
        cout << hld.dist(u-1,v-1)+1 << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    // Vertex_Add_Path_Sum();
    // Lowest_Common_Ancestor();
    // AOJ_LCA();
    ABC014_D();
}
