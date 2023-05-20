/**
*    author:  shu8Cream
*    created: 09.05.2023 21:20:17
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

template<typename flow_t>
struct Dinic {
    const flow_t inf;
    struct edge {
        int to;
        flow_t cap;
        int rev;
        bool isrev;
        int id;
    };
    vv<edge> g;
    vc<int> min_cost;
    vc<int> iter;
    Dinic(int n): inf(numeric_limits<flow_t>::max()),g(n){}
    
    void addEdge(int from, int to, flow_t cap, int id=-1){ 
        g[from].emplace_back(edge{to,cap,sz(g[to]),false,id});
        g[to].emplace_back(edge{from,0,sz(g[from])-1,true,id});
    }
    bool bfs(int s,int t){
        min_cost.assign(sz(g),-1);
        min_cost[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()&&min_cost[t]==-1){
            int p = q.front(); q.pop();
            for(auto &e: g[p]){
                if(e.cap>0&&min_cost[e.to]==-1){
                    min_cost[e.to] = min_cost[p] + 1;
                    q.push(e.to);
                }
            }
        }
        return min_cost[t]!=-1;
    }
    flow_t dfs(int id, int t, flow_t f) {
        if(id==t) return f;
        for(int &i=iter[id]; i<sz(g[id]); i++){
            edge &e = g[id][i];
            if(e.cap>0&&min_cost[id]<min_cost[e.to]){
                flow_t d = dfs(e.to,t,min(f,e.cap));
                if(d>0){
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    flow_t max_flow(int s, int t) {
        flow_t flow = 0;
        while(bfs(s,t)){
            iter.assign(sz(g),0);
            flow_t f = 0;
            while((f=dfs(s,t,inf))>0) flow+=f;
        }
        return flow;
    }
};

void GRL6_A(){
    int V,E; cin >> V >> E;
    Dinic<ll> to(V);
    rep(i,E){
        int u,v; ll c; cin >> u >> v >> c;
        to.addEdge(u,v,c,i);
    }
    cout<<to.max_flow(0,V-1)<<endl;
}

// unsolve
void ARC031D(){
    int n,m; cin >> n >> m;
    vi s(n); cin >> s;
    vi t(m); cin >> t;
    vvi a(n);
    rep(i,n){
        int k; cin >> k;
        a[i].resize(k);
        cin >> a[i];
    }

}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    // GRL6_A();
    ARC031D();
}
