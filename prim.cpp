/**
 * @file prim.cpp
 * @author shu8Cream
 * @brief 
 * @version 0.1
 * @date 2022-05-22
 * @verify https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_A
 * 
 * プリム法
 * 最小全域木を求めるアルゴリズム
 * 
 * 計算量
 * O(ElogV)
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

struct edge {
    int from, to;
    ll cost;
};
vc<int> tree;

ll prim(vv<edge> &edges, int v, int s){
    using Pi = pair<ll, pair<int,int>>;
    ll res = 0;
    vc<bool> used(v);
    tree.resize(v);
    priority_queue<Pi, vc<Pi>, greater<Pi>> pq;
    pq.push({0,{s,s}});
    while(!pq.empty()){
        auto [pf,ps] = pq.top(); pq.pop();
        auto [psf,pss] = ps;
        if(used[psf]) continue;
        used[psf] = true;
        tree[psf] = pss;
        res += pf;
        for(edge &e : edges[psf]){
            if(!used[e.to]) pq.push({e.cost,{e.to,psf}});
        }
    }
    return res;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n,m; cin >> n >> m;
    vv<edge> vec(n);
    rep(i,m){
        int a,b; ll w; cin >> a >> b >> w;
        vec[a].push_back({a,b,w});
        vec[b].push_back({b,a,w});
    }
    ll min_cst = prim(vec,n,0);
    cout << min_cst << endl;
}