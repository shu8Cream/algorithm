//  
//  Dijkstra(ダイクストラ法、正辺のみ)
//
/*

    単一視点最短路問題
    計算量：ヒープなしO(V^2）、ヒープありO(ElogV)
    最短経路木
    始点から各頂点への距離の和が最短になるように構成した全域木。

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

struct edge {int to; ll cost; int id;};

vi dist;
// 最短経路木
vc<int> tree;

// edges:グラフ, V:頂点数, s:始点 を与える
void dijkstra(vv<edge> &edges, int V, int s){
    dist.resize(V,INF); dist[s] = 0;
    priority_queue<P, vector<P>, greater<P>> q;
    tree.resize(V-1);
    q.push(P(0, s));
    while (!q.empty()) {
        P p = q.top(); q.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (auto e : edges[v]) {
            if (dist[e.to] > dist[v] + e.cost) {
                dist[e.to] = dist[v] + e.cost;
                q.push(P(dist[e.to], e.to));
                tree[e.to-1] = e.id+1;
            }
        }
    }
}

int main(){
    int n,m; cin >> n >> m;
    vv<edge> to(n);
    rep(i,m){
        int s,t; ll w; cin >> s >> t >> w;
        s--; t--;
        to[s].push_back((edge){t,w,i});
        to[t].push_back((edge){s,w,i});
    }
    dijkstra(to,n,0);
    // 最短経路木を構成する辺の集合
    cout << tree << endl;
    rep(i,n){
        if(dist[i]==INF) cout << "INF" << endl;
        else cout << dist[i] << endl;
    }
}