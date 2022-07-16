/**
 * @file xorshift.cpp
 * @author shu8Cream
 * @brief 
 * @version 0.1
 * @date 2022-05-10
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

// 周期は2^128-1
struct Xorshift{
    unsigned int x,y,z,w;
    Xorshift(unsigned int x=123456789, unsigned int y=362436069, unsigned int z=521288629, unsigned int w=88675123) : x(x),y(y),z(z),w(w) {
        assert(x!=0 || y!=0 || z!=0 || w!=0);
    }
    unsigned int operator()(){
        unsigned int t = x ^ (x << 11);
        x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)); 
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ll n; cin >> n;
    vi a(n); cin >> a;
    vi b(n); cin >> b;
    map<ll,ll> mp;
    vi xa(n),xb(n);
    set<ll> bst;
    Xorshift x128;
    rep(i,n){
        if(!mp.count(a[i])){
            xa[i] = x128();
            mp[a[i]] = xa[i];
        }
    }
    rep(i,n){
        if(!mp.count(b[i])){
            xb[i] = x128();
            mp[b[i]] = xb[i];
            bst.insert(b[i]);
        }else if(!bst.count(b[i])){
            bst.insert(b[i]);
            xb[i] = mp[b[i]];
        }
    }
    debug(xa);
    debug(xb);
    vi rxa(n+1),rxb(n+1);
    rep(i,n) rxa[i+1] = rxa[i]^xa[i];
    rep(i,n) rxb[i+1] = rxb[i]^xb[i];
    int q; cin >> q;
    rep(qi,q){
        int x,y; cin >> x >> y;
        cout << (rxa[x]==rxb[y] ? "Yes" : "No") << endl;
    }
}