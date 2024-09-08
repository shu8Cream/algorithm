/**
*    author:  shu8Cream
*    created: 09.01.2023 17:40:17
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

using i128 = __int128_t;

struct Miller_Rabin{
    const vi v32 = {2,7,61};
    const vi v64 = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    
    template <class T>
    inline T mod_pow(T a, ll b, T n){
        T res = 1;
        a%=n;
        while(b){
            if(b&1) res = res * a % n;
            b>>=1;
            a = a * a % n;
        }
        return res;
    }

    bool check(i128 n){
        if(n==1) return false;
        if(n==2) return true;
        if(n%2==0) return false;
        auto judge = [&](auto vec)->bool{
            i128 d = n-1;
            d = d/(d&-d);
            for(i128 a:vec){
                if(n<=a) break;
                i128 t = d;
                i128 y = mod_pow(a,t,n);
                if(y==1) continue;
                while(y!=n-1){
                    y = mod_pow(y,2,n);
                    if(y==1 || t==n-1) return false;
                    t<<=1;
                }
            }
            return true;
        };
        if(n<4'759'123'141) return judge(v32);
        else return judge(v64);
    }
};


ll pollard(ll n){
    if(n%2==0) return 2;
    Miller_Rabin mr;
    if(mr.check(n)) return n;

    ll step = 0;
    auto f = [&](ll x)->ll{
        return (i128(x) * x + step) % n;
    };

    while(1){
        step++;
        ll x = step, y = f(x);
        while(1){
            ll p = gcd(y-x+n, n);
            if(p==0 || p==n) break;
            if(p!=1) return p;
            x = f(x);
            y = f(f(y));
        }
    }
}

vi prime_factorize(ll n){
    if(n==1) return {};
    ll p = pollard(n);
    if(p==n) return {n};
    vi left = prime_factorize(p);
    vi right = prime_factorize(n/p);
    left.insert(left.begin(), all(right));
    sort(all(left));
    return left;
}

void algo_logic(){
    ll n; cin >> n;
    vi a(n); cin >> a;
    rep(i,n) cout << prime_factorize(a[i]) << endl;
}

void solve(){
    ll n; cin >> n;
    vi p = prime_factorize(n);
    // cout << p[1] << " " << (p[1]==p[2]? p[0]:p[2]) << endl;
    cout << p << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    // algo_logic();
    int t; cin >> t;
    for(;t--;) solve();
}
