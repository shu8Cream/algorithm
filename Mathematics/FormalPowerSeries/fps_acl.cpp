/**
*    author:  shu8Cream
*    created: 2025/12/01 15:33:02
**/

#include <bits/stdc++.h>
#include <atcoder/all>
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

using mint = atcoder::modint998244353;
istream& operator>>(istream& is, mint& a) { long long v; is >> v; a = mint(v); return is;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.val();}
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
#define debug(...) do { cout << "[DEBUG] "; debug_out(__VA_ARGS__); } while(0);
#else
#define debug(...)
#endif

using FPS = vector<mint>;

FPS operator*(FPS a, FPS b){
    return atcoder::convolution(a, b);
}
FPS &operator*=(FPS &a, FPS b){
    a = a * b;
    return a;
}

FPS operator+(FPS a, FPS b){
    if(a.size() < b.size()) swap(a,b);
    for(int i=0; i<b.size(); i++) a[i] += b[i];
    return a;
}
FPS &operator+=(FPS &a, FPS b){
    a = a + b;
    return a;
}

FPS operator-(FPS a, FPS b){
    if(a.size() < b.size()) a.resize(b.size());
    for(int i=0; i<b.size(); i++) a[i] -= b[i];
    return a;
}
FPS &operator-=(FPS &a, FPS b){
    a = a - b;
    return a;
}

FPS operator*(mint k, FPS f){
    for(auto &e:f) e *= k;
    return f;
}
FPS operator*(FPS f, mint k){
    for(auto &e:f) e *= k;
    return f;
}
FPS &operator*=(FPS &f, mint k){
    f = f * k;
    return f;
}

FPS inv(FPS a){
    int length = a.size();
    FPS x = {a[0].inv()};
    while(x.size() < length) {
        int new_length = x.size() * 2;
        x.resize(new_length,0);
        auto tmp = FPS(a.begin(), a.begin() + min(a.size(), x.size()));
        x = (FPS{2} - tmp * x) * x;
        x.resize(new_length);
    }
    x.resize(length);
    return x;
}

FPS operator/(FPS f, FPS g){
    return f * inv(g);
}
FPS &operator/=(FPS &f, FPS g){
    f = f / g;
    return f;
}

FPS operator/(FPS f, mint k){
    return f * k.inv();
}
FPS &operator/=(FPS &f, mint k){
    f = f * k.inv();
    return f;
}

FPS log(FPS f){
    FPS f_prime(f.begin()+1, f.end());
    for(int i=0; i<f_prime.size(); i++){
        f_prime[i] *= i + 1;
    }
    FPS x = f_prime / f;
    x.insert(x.begin(), 0);
    x.resize(f.size());
    for(int i=1; i<x.size(); i++){
        x[i] /= i;
    }
    return x;
}

FPS exp(FPS f){
    int length = f.size();
    FPS x = {1};
    while(x.size() < length) {
        int new_length = x.size() * 2;
        x.resize(new_length,0);
        x = x * (FPS{1} - log(x) + FPS(f.begin(), f.begin() + min(f.size(), x.size())));
        x.resize(new_length);
    }
    x.resize(length);
    return x;
}

void test_inv_fps() {
    ll n; cin >> n;
    FPS a(n); cin >> a;
    auto ans = inv(a);
    cout << ans << endl;
}

void test_exp_fps() {
    ll n; cin >> n;
    FPS a(n); cin >> a;
    auto ans = exp(a);
    cout << ans << endl;
}

void test_log_fps() {
    ll n; cin >> n;
    FPS a(n); cin >> a;
    auto ans = log(a);
    cout << ans << endl;
}

// void test_pow_fps() {
//     ll n,m; cin >> n >> m;
//     FPS a(n); cin >> a;
//     auto ans = pow(a,m);
//     cout << ans << endl;
// }

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    // test_inv_fps();
    // test_log_fps();
    // test_exp_fps();
    // test_pow_fps();
}