//  
//  LCA(Loweset Common Ancestor)
//
/*

    最近共通祖先をダブリングによって求める。
    計算量：前処理O(NlogN）、クエリO(logN)

    応用
    ２点間の距離　get_dist
    ２点間にある頂点aが存在しているかの判定　is_on_path
    頂点uからk個上に登る　climb

*/

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

int Log2(ll x){
    if(x==0) return 0;
    using ull = unsigned long long;
    return 63 - __builtin_clzll(ull(x));
}

struct LCA{
    int n;
    vvi parent;
    vi dep;
    LCA(const vvi &G, int root = 0):n(sz(G)){ init(G,root); }

    void init(const vvi &G, int root = 0){
        int k = Log2(n)+1;
        parent.assign(k,vi(n,-1));
        dep.assign(n,-1);
        dfs(G, root, -1, 0);
        rep(i,parent.size()-1)rep(j,n){
            if(parent[i][j]!=-1) parent[i+1][j]=parent[i][parent[i][j]];
        }
    }

    void dfs(const vvi &G, int v, int p, int d){
        parent[0][v]=p;
        dep[v]=d;
        for(auto e : G[v]) if(e!=p) dfs(G,e,v,d+1);
    }

    int query(int u, int v){
        if(dep[u] < dep[v]) swap(u,v);
        int k = parent.size();
        rep(i,k){
            if((dep[u]-dep[v]) >> i & 1){
                u = parent[i][u];
            }
        }
        if(u==v) return u;
        for(int i=k-1; i>=0; i--){
            if(parent[i][u] != parent[i][v]){
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        return parent[0][u];
    }

    int get_dist(int u, int v) { 
        return dep[u] + dep[v] - 2 * dep[query(u, v)];
    }

    bool is_on_path(int u, int v, int a) {
        return get_dist(u, a) + get_dist(a, v) == get_dist(u, v);
    }

    // uから根に向かってk個登る
    int climb(int u, int k){
        if(dep[u]<k) return -1;
        int LOG = Log2(n);
        rrep(i,LOG+1)if((k>>i)&1) u = parent[i][u];
        return u;
    }
};

int main(){
    int n;
    cin >> n;
    vvi G(n);
    rep(i,n){
        int k; cin >> k;
        rep(j,k){
            int c; cin >> c;
            G[i].push_back(c);
            G[c].push_back(i);
        }
    }
    LCA lca(G);
    int q; cin >> q;
    rep(i,q){
        int u,v; cin >> u >> v;
        cout << lca.query(u,v) << endl;
    }
}
