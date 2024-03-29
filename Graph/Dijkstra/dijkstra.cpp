/**
*    author:  shu8Cream
*    created: 05.03.2023 23:37:08
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

template<typename T>
struct Dijkstra {
    const T inf = numeric_limits<T>::max();
    using PT = pair<T,int>;
    struct Edge {
        int to; T cost; int id;
        Edge(){}
        Edge(int to, T cost, int id=0): to(to),cost(cost), id(id){}
    };
    int n;
    vv<Edge> g;
    vi pre;
    vc<int> tree;
    Dijkstra(){}
    Dijkstra(int n): n(n), g(n), pre(n,-1), tree(n,-1){}

    void addEdge(int u, int v, T cost, int id=0, bool both=false){
        g[u].emplace_back(v,cost,id);
        if(both) g[v].emplace_back(u,cost,id);
    }

    vc<T> getDist(int s){
        vc<T> dist(n,inf); dist[s] = 0;
        priority_queue<PT, vector<PT>, greater<PT>> q;
        q.emplace(0, s);
        while (sz(q)) {
            auto[d,v] = q.top(); q.pop();
            if (dist[v]!=d) continue;
            for (auto e : g[v]) {
                ll nd = d+e.cost;
                if (dist[e.to] > nd) {
                    dist[e.to] = nd;
                    q.emplace(dist[e.to], e.to);
                    pre[e.to] = v;
                    tree[e.to] = e.id;
                }
            }
        }
        return dist;
    }

    vi restore(int t){
        vi path;
        for (; t != -1; t = pre[t]) path.push_back(t);
        reverse(all(path));
        return path;
    }
};

void GRL_1_A(){
    int n,m,r; cin >> n >> m >> r;
    Dijkstra<ll> to(n);
    rep(i,m){
        int s,t; ll w; cin >> s >> t >> w;
        to.addEdge(s,t,w);
    }
    auto d = to.getDist(r);
    rep(i,n){
        if(d[i]==to.inf) cout << "INF" << endl;
        else cout << d[i] << endl;
    }
}

void ABC252E(){
    int n,m; cin >> n >> m;
    Dijkstra<ll> to(n);
    rep(i,m){
        int a,b; ll c;
        cin >> a >> b >> c; a--,b--;
        to.addEdge(a,b,c,i,true);
    }
    auto d = to.getDist(0);
    rep(i,1,n) cout<<to.tree[i]+1<<(i==n-1?'\n':' ');
}

void ABC168D(){
    int n,m; cin >> n >> m;
    Dijkstra<ll> to(n);
    rep(i,m){
        int u,v; cin >> u >> v, u--, v--;
        to.addEdge(u,v,1,i,true);
    }
    vi dist = to.getDist(0);
    vi ans(n-1);
    rep(i,n-1){
        ans[i] = to.pre[i+1]+1;
    }
    cout<<"Yes"<<endl;
    cout<<ans<<endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    // GRL_1_A();
    // ABC252E();
    ABC168D();
}
