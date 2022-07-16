//
//  強連結成分分解（Strongly Connected Component）
//
/*

    強連結成分分解をしたグラフを再構築できる（build）
    verify ABC245 F-Endless Walk 
    提出；https://atcoder.jp/contests/abc245/submissions/30512611

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

struct SCC{
    const vvi &to;
    vv<int> G, rG;
    vc<int> order, tp_order, seen;

    SCC(vvi &to) : to(to), G(sz(to)), rG(sz(to)), order(sz(to)), tp_order(sz(to),-1), seen(sz(to)) {
        rep(i,sz(to)){
            for(auto v:to[i]){
                G[i].emplace_back(v);
                rG[v].emplace_back(i);
            }
        }
    }

    int operator[](int id){
        return tp_order[id];
    }

    void dfs(int s){
        if(seen[s]) return;
        seen[s] = 1;
        for(auto nv:G[s]) dfs(nv);
        order.emplace_back(s);
    }

    void rdfs(int s, int cnt){
        if(tp_order[s]!=-1) return;
        tp_order[s] = cnt;
        for(auto nv:rG[s]) rdfs(nv,cnt);
    }

    vvi build(){
        rep(i,sz(to)) dfs(i);
        reverse(all(order));
        int tp_num = 0;
        for(int e:order)if(tp_order[e]==-1) rdfs(e,tp_num++);
        vvi res(tp_num);
        rep(i,sz(to)){
            for(auto nv:to[i]){
                int a = tp_order[i];
                int b = tp_order[nv];
                if(a==b) continue;
                res[a].emplace_back(b);
            }
        }
        return res;
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n,m; cin >> n >> m;
    vvi to(n);
    rep(i,m){
        int u,v; cin >> u >> v;
        u--; v--;
        to[u].emplace_back(v);
    }
    SCC scc(to);
    vvi scc_to = scc.build();
    map<int,int> mp;
    rep(i,sz(to)) mp[scc[i]]++;
    int k = sz(scc_to);
    vvi rto(k);
    rep(i,k)for(auto p:scc_to[i]) rto[p].emplace_back(i);
    vc<int> dp(k);
    int ans = 0;
    for(auto[k,v]:mp){
        if(v>1){
            ans+=v;
            dp[k] = 1;
        }
    }
    rrep(i,k)for(auto p:rto[i]) dp[p]|=dp[i];
    rep(i,k)if(dp[i] && mp[i]==1) ans++;
    cout << ans << endl;
}