/**
*    author:  shu8Cream
*    created: 08.01.2023 01:07:26
*
*    下記を改良
*    https://ei1333.github.io/luzhiled/snippets/string/rolling-hash.html
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

using ull = unsigned long long;

const ull mod = (1ULL<<61) - 1;
chrono::system_clock::time_point tp = chrono::system_clock::now();
// エポックからの経過時間
chrono::microseconds tp_micro_sec = chrono::duration_cast<chrono::microseconds>(tp.time_since_epoch());
const ull base = tp_micro_sec.count() % mod;

struct RollingHash {
    vector<ull> hashed, power;

    static constexpr ull mask(ll x){ return (1ULL << x) - 1; }

    inline ull mul(ull a, ull b) const {
        //*
        // int128が使えるならこっち
        __uint128_t t = __uint128_t(a) * b;
        /*/
        ull au = a>>31, bu = b>>31;
        ull ad = a & mask(31), bd = b & mask(31);
        ull m = ad * bu + bd * au;
        ull mu = m>>30;
        ull md = m & mask(30);
        ull t = au * bu * 2 + mu + (md<<31) + ad * bd;
        //*/
        t = (t >> 61) + (t & mod);
        if(t >= mod) return t - mod;
        return t;
    }

    RollingHash(const string &s) {
        ll n = (ll) s.size();
        hashed.assign(n + 1, 0);
        power.assign(n + 1, 0);
        power[0] = 1;
        for(ll i = 0; i < n; i++) {
            power[i + 1] = mul(power[i], base);
            hashed[i + 1] = mul(hashed[i], base) + s[i];
            if(hashed[i + 1] >= mod) hashed[i + 1] -= mod;
        }
    }

    ull get(ll l, ll r) const {
        ull ret = hashed[r] + mod - mul(hashed[l], power[r - l]);
        if(ret >= mod) ret -= mod;
        return ret;
    }

    ull connect(ull h1, ull h2, ll h2len) const {
        ull ret = mul(h1, power[h2len]) + h2;
        if(ret >= mod) ret -= mod;
        return ret;
    }

    ll LCP(const RollingHash &b, ll l1, ll r1, ll l2, ll r2) {
        ll len = min(r1 - l1, r2 - l2);
        ll low = -1, high = len + 1;
        while(high - low > 1) {
            ll mid = (low + high) / 2;
            if(get(l1, l1 + mid) == b.get(l2, l2 + mid)) low = mid;
            else high = mid;
        }
        return (low);
    }
};

// want to solve: https://codeforces.com/contest/1129/problem/C

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ll n; cin >> n;
    string t; cin >> t;
    string rt = t;
    reverse(all(rt));
 
    string T = t+rt;
    RollingHash rh(T);
    rep(i,1,n){
        auto h1 = rh.get(0,i);
        auto h2 = rh.get(i+n, 2*n);
        auto v1 = rh.connect(h1,h2,n-i);
        auto v2 = rh.get(3*n-i, 4*n-i);
        if(v1==v2){
            string s = rt.substr(n-i,n);
            cout << s << endl;
            cout << i << endl;
            return 0;
        }
    }
    string s = t.substr(n,n);
    reverse(all(s));
    if(s==t.substr(0,n)){
        cout << s << endl;
        cout << n << endl;
        return 0;
    }
    cout << -1 << endl;
}
