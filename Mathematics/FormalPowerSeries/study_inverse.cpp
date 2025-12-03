/**
*    author:  shu8Cream
*    created: 2025/11/25 19:57:55
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
template <class T> string to_string(complex<T> s);
template <class S, class T> string to_string(pair<S, T> p);
template <class... Tp> string to_string(tuple<Tp...>& t);
string to_string(char c) { return string(1, c); }
string to_string(string s) { return s; }
string to_string(const char s[]) { return string(s); }

template <class T>
string to_string(complex<T> s) {
    return "(" + to_string(s.real()) + "+" + to_string(s.imag()) + "i)";
}

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
template<typename... Tp>
string to_string(tuple<Tp...>& t) {
    string ret = "{";
    std::apply([&](const auto&... args) {
        ((ret += to_string(args) + ","), ...);
    }, t);
    if constexpr (sizeof...(Tp) > 0) ret.back() = '}';
    else ret += "}";
    return ret;
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

/*
const int mod = 1000000007;
/*/
const int mod = 998244353;
//*/
struct mint{
    ll x;
    mint(ll x=0):x((x%mod+mod)%mod){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += mod-a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= mod; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        mint a = *this, r = 1;
        while(t){
            if(t&1) r *= a;
            a *= a;
            t >>= 1;
        }
        return r;
    }

    mint inv() const { return this->pow(mod-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}

    bool operator==(const mint &other) const {
        return x == other.x;
    }
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

using at_mint = atcoder::modint998244353;

unsigned int ceil_pow2(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x <<= 1;
    return x;
}

// 離散フーリエ変換 (Discrete Fourier Transform)
vector<complex<double>> dft_fp(vector<complex<double>> A){
    const int N = A.size();
    int N2 = ceil_pow2(N);
    A.resize(N2);
    vector<complex<double>> B(N2);
    for(int i = 0; i < N2; i++) for(int j = 0; j < N2; j++){
        B[i] += A[j] * polar(1.0, 2.0 * M_PI * i * j / double(N2));
    }
    return B;
}

// 逆離散フーリエ変換 (Inverse Discrete Fourier Transform)
vector<complex<double>> idft_fp(vector<complex<double>> B){
    const int N = B.size();
    int N2 = ceil_pow2(N);
    B.resize(N2);
    vector<complex<double>> A(N2);
    for(int i = 0; i < N2; i++) for(int j = 0; j < N2; j++){
        A[i] += B[j] * polar(1.0, -2.0 * M_PI * i * j / double(N2));
    }
    for(int i = 0; i < N2; i++) A[i] /= N2;
    return A;
}

vector<mint> dft(vector<mint> a) {
    int n = a.size();
    int n2 = ceil_pow2(n);
    a.resize(n2);
    vector<mint> b(n2);
    mint w = mint(3).pow((mod-1)/n2);
    for(int i=0; i<n2; i++)for(int j=0; j<n2; j++){
        b[i] += a[j] * w.pow(i*j);
    }
    return b;
}

vector<mint> idft(vector<mint> b) {
    int n = b.size();
    int n2 = ceil_pow2(n);
    b.resize(n2);
    vector<mint> a(n2);
    mint w = mint(3).pow((mod-1) / n2);
    // w = w.pow(n2-1);
    for(int i=0; i<n2; i++)for(int j=0; j<n2; j++){
        a[i] += b[j] / w.pow(i*j);
    }
    for(int i=0; i<n2; i++) a[i] /= n2;
    return a;
}

vector<mint> convolution_dft(vector<mint> a, vector<mint> b) {
    int ret_size = a.size() + b.size() - 1;
    int n = max(ceil_pow2(a.size()), ceil_pow2(b.size())) << 1;
    a.resize(n);
    b.resize(n);
    vector<mint> ad = dft(a);
    vector<mint> bd = dft(b);
    cerr << n << endl;
    rep(i,n) cerr << ad[i] << (i==n-1 ? '\n':' ');
    rep(i,n) cerr << bd[i] << (i==n-1 ? '\n':' ');
    for(int i=0; i<n; i++) ad[i] *= bd[i];
    vector<mint> c = idft(ad);
    c.resize(ret_size);
    return c;
}

vector<mint> fft(vector<mint> a, mint w = 0) {
    int n = a.size();
    if(w == 0) w = mint(3).pow((mod-1) / n);
    if(n == 1) return a;
    vector<mint> even(n / 2), odd(n / 2);
    for(int i=0; i<n/2; i++){
        even[i] = a[i*2];
        odd[i]  = a[i*2 + 1];
    }
    auto E = fft(even, w*w);
    auto O = fft(odd,  w*w);
    vector<mint> A(n);
    auto wi = mint(1);
    for(int i=0; i<n; i++){
        A[i] = E[i % (n/2)] + wi * O[i % (n/2)];
        wi *= w;
    }
    return A;
}

vector<mint> ifft(vector<mint> A) {
    reverse(A.begin()+1, A.end());
    auto a = fft(A);
    int n = A.size();
    for(auto &x:a) x /= mint(n);
    return a;
}

vector<mint> convolution(vector<mint> a, vector<mint> b){
    int n = 1;
    int ret_size = a.size() + b.size() - 1;
    while(n < a.size() * 2 || n < b.size() * 2) n <<= 1;
    a.resize(n,0);
    b.resize(n,0);
    auto A = fft(a);
    auto B = fft(b);
    for(int i=0; i<n; i++) A[i] *= B[i];
    auto c = ifft(A);
    c.resize(ret_size);
    return c;
}

vector<mint> operator+(vector<mint> a, vector<mint> b){
    vector<mint> ret(max(a.size(), b.size()));
    for(int i=0; i<a.size(); i++) ret[i] += a[i];
    for(int i=0; i<b.size(); i++) ret[i] += b[i];
    return ret;
}

vector<mint> operator-(vector<mint> a, vector<mint> b){
    vector<mint> ret(max(a.size(), b.size()));
    for(int i=0; i<a.size(); i++) ret[i] += a[i];
    for(int i=0; i<b.size(); i++) ret[i] -= b[i];
    return ret;
}

vector<mint> operator*(mint k, vector<mint> a){
    for(auto &x:a) x *= k;
    return a;
}

vector<mint> inv_fps(vector<mint> a){
    int d = 1;
    vector<mint> ret = {a[0].inv()};
    while(d < a.size()) {
        d *= 2;
        ret.resize(d,0);
        auto tmp = vector(a.begin(), a.begin() + min(a.size(), ret.size()));
        ret = 2 * ret - convolution(tmp, convolution(ret, ret));
        ret.resize(d);
    }
    ret.resize(a.size());
    return ret;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ll n; cin >> n;
    vc<mint> a(n); cin >> a;
    auto ans = inv_fps(a);
    cout << ans << endl;
}