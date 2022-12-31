/**
 * @file namori.cpp
 * @author shu8Cream
 * @brief 
 * @version 0.1
 * @date 2022-08-30
 * 
 * @verify https://atcoder.jp/contests/abc266/tasks/abc266_f
 * 
 * なもりグラフ（N頂点N辺の無向グラフ）
 * 
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

struct Namori{
    vvi g;
    vi in;
    Namori(vvi g): g(g),in(sz(g)){}

    // forest: 枝を受け取る、loop: 閉路を受け取る
    void build(vvi &forest, vi &loop){
        int n = sz(g);
        forest.resize(n);
        rep(i,n)for(auto p:g[i]) in[p]++;
        queue<int> q;
        vc<bool> seen(n);
        rep(i,n)if(in[i]==1){
            q.push(i);
            seen[i] = 1;
        }
        while(sz(q)){
            int v = q.front(); q.pop();
            for(auto nv:g[v]){
                if(seen[nv]) continue;
                in[nv]--;
                forest[v].push_back(nv);
                forest[nv].push_back(v);
                if(in[nv]>1) continue;
                seen[nv] = 1;
                q.push(nv);
            }
        }

        auto dfs = [&](auto dfs, int s)->void{
            loop.push_back(s);
            for(auto v:g[s]){
                if(seen[v]) continue;
                seen[v] = 1;
                dfs(dfs,v);
            }
        };

        rep(i,n){
            if(seen[i]) continue;
            seen[i] = 1;
            dfs(dfs,i);
            break;
        }
    }
};

struct UnionFind{
    vector<int> par;
    UnionFind(){}
    UnionFind(int n=0): par(n, -1) {}
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
        return true;
    }
    bool same(int x, int y) {return find(x) == find(y);}
    int size(int x) {return -par[find(x)];}
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n; cin >> n;
    vvi to(n);
    rep(i,n){
        int u,v; cin >> u >> v, u--, v--;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    Namori nmr(to);
    vvi tr; vi loop;
    nmr.build(tr,loop);
    set<ll> st;
    for(auto p:loop) st.insert(p);
 
    UnionFind uf(n);
    rep(i,n)for(auto p:tr[i]) uf.merge(i,p);
 
    int q; cin >> q;
    rep(qi,q){
        int x,y; cin >> x >> y, x--, y--;
        cout << (uf.same(x,y) ? "Yes" : "No") << endl;
    }
}