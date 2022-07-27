/**
 * @file LCA_euler_tour.cpp
 * @author shu8Cream
 * @brief 
 * @version 0.1
 * @date 2022-07-24
 * 
 * @verify https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_C
 *         https://judge.yosupo.jp/problem/lca
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
const ll INF = 8e18;
template<typename T>istream& operator>>(istream&i,vc<T>&v){rep(j,sz(v))i>>v[j];return i;}
template<typename T>string join(const T&v,const string& d=""){stringstream s;rep(i,sz(v))(i?s<<d:s)<<v[i];return s.str();}
template<typename T>ostream& operator<<(ostream&o,const vc<T>&v){if(sz(v))o<<join(v," ");return o;}
template<typename T1,typename T2>istream& operator>>(istream&i,pair<T1,T2>&v){return i>>v.first>>v.second;}
template<typename T1,typename T2>ostream& operator<<(ostream&o,const pair<T1,T2>&v){return o<<v.first<<","<<v.second;}
template<class T> inline bool chmax(T& a, T b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) { a = b; return true; }
    return false;
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

template<typename T>
struct SparseTable{
    vv<T> table;
    SparseTable(){}
    SparseTable(vc<T> &arr) {
        int n = sz(arr);
        int len = 0;
        while((1<<len)<=n) len++;
        table.resize(len);
        table[0] = arr;
        rep(i,1,len){
            assert(n-(1<<i)+1>0);
            table[i].resize(n-(1<<i)+1);
            rep(j,n-(1<<i)+1){
                table[i][j] = min(table[i-1][j],table[i-1][j+(1<<(i-1))]);
            }
        }
    }

    void debug_view(){
        rep(i,sz(table)) cerr << table[i] << endl;
    }

    // [l,r), 0-indexed
    T query(int l, int r){
        assert(l<r);
        int rng = r-l;
        int lg = 31 - __builtin_clz(rng);
        assert(r-(1<<lg)>=0);
        return min(table[lg][l], table[lg][r-(1<<lg)]);
    }
};

struct LCA{
    int n;
    vv<int> G;
    vc<int> in,out,par,edge,dep;
    SparseTable<P> sp;
    LCA(){}
    LCA(int n): n(n),G(n),in(n),out(n),par(n,-1),
        edge(n*2),dep(n*2){}

    void add_edge(int u, int v){
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void build(int root=0){
        int time = 0;
        dfs(root,time);
        rep(i,n*2-1)dep[i+1] = dep[i]+(edge[i+1]>0?1:-1);
        vc<P> vec(n*2);
        rep(i,n*2) vec[i] = {dep[i],edge[i]};
        sp = SparseTable(vec);
    }
    // 2頂点のLCA
    int lca(int u, int v){
        if(in[u]>in[v]) swap(u,v);
        P a =  sp.query(in[u],in[v]+1);
        debug(u,v,in[u],in[v]);
        debug(a.first,a.second);
        if(a.second>0) return (dep[in[u]]<=dep[in[v]]? u:v);
        else return par[-a.second-1];
    }
    // 集合のLCA
    int lca(vc<int> &vertexs){
        int mn = vertexs[0], mx = vertexs[0];
        for(int &p:vertexs){
            if(in[mn]>in[p]) mn = p;
            if(in[mx]<in[p]) mx = p;
        }
        return lca(mn,mx);
    }

    int dist(int u, int v){
        return dep[in[u]]+dep[in[v]]-2*dep[in[lca(u,v)]];
    }

private:
    void dfs(int v, int &time){
        in[v] = time++;
        edge[in[v]] = v+1;
        for(int &nv:G[v]){
            if(nv==par[v]) continue;
            par[nv] = v;
            dfs(nv,time);
        }
        out[v] = time++;
        edge[out[v]] = -v-1;
    }
};

void AOJ_LCA() {
    int n,q; cin >> n;
    LCA lca(n);
    rep(i,n){
        int k; cin >> k;
        rep(j,k){
            int c; cin >> c;
            lca.add_edge(i,c);
        }
    }
    lca.build();
    // cout << lca.in << endl;
    // cout << lca.out << endl;
    // cout << lca.edge << endl;
    // cout << lca.dep << endl;
    // cout << lca.par << endl;

    cin >> q;
    rep(qi,q){
        int u,v; cin >> u >> v;
        cout << lca.lca(u,v) << endl;
    }
}

void Lowest_Common_Ancestor(){
    int n,q; cin >> n >> q;
    LCA lca(n);
    rep(i,1,n){
        int p; cin >> p;
        lca.add_edge(i,p);
    }
    lca.build();

    rep(qi,q){
        int u,v; cin >> u >> v;
        cout << lca.lca(u,v) << endl;
    }
}

void ABC014_D(){
    int n; cin >> n;
    LCA lca(n);
    rep(i,n-1){
        int x,y; cin >> x >> y;
        lca.add_edge(x-1,y-1); 
    }
    lca.build();
    int q; cin >> q;
    rep(qi,q){
        int u,v; cin >> u >> v;
        cout << lca.dist(u-1,v-1)+1 << endl;
    }
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    // AOJ_LCA();
    // Lowest_Common_Ancestor();
    ABC014_D();
}