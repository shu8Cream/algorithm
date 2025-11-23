/**
*    author:  shu8Cream
*    created: 2025/11/23 16:12:50
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

// 離散フーリエ変換 (Discrete Fourier Transform)
vector<complex<double>> DFT(vector<complex<double>> A){
    const int N = A.size();
    vector<complex<double>> B(N);
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++){
        B[i] += A[j] * polar(1.0, 2.0 * M_PI * i * j / double(N));
    }
    return B;
}

// 逆離散フーリエ変換 (Inverse Discrete Fourier Transform)
vector<complex<double>> IDFT(vector<complex<double>> B){
    const int N = B.size();
    vector<complex<double>> A(N);
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++){
        A[i] += B[j] * polar(1.0, -2.0 * M_PI * i * j / double(N));
    }
    for(int i = 0; i < N; i++) A[i] /= N;
    return A;
}

// 畳み込み (Convolution)
vector<complex<double>> Convolution(vector<complex<double>> A, vector<complex<double>> B){
    const int N = A.size();
    const int M = B.size();
    const int L = N + M - 1;
    A.resize(L);
    B.resize(L);

    vector<complex<double>> FA = DFT(A);
    vector<complex<double>> FB = DFT(B);
    vector<complex<double>> FC(L);
    debug(FA);
    debug(FB);
    for(int i = 0; i < L; i++) FC[i] = FA[i] * FB[i];
    debug(FC);
    vector<complex<double>> C = IDFT(FC);
    return C;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    cout << "input >> block_num" << endl;
    cout << "   1: DFT/IDFT" << endl;
    cout << "   2: Convolution" << endl;
    int block_num; cin >> block_num;
    if(block_num == 1) { // DFT, IDFTの確認
        ll n; cin >> n;
        vc<complex<double>> a(n); cin >> a;
        vc<complex<double>> b = DFT(a);
        cout << "DFT: " <<  b << endl;

        vc<complex<double>> c = IDFT(b);
        cout << "IDFT: " << c << endl;
    }
    if(block_num == 2) { // Convolutionの確認
        ll n; cin >> n;
        vc<complex<double>> a(n), b(n);
        cin >> a;
        cin >> b;
        vc<complex<double>> c = Convolution(a, b);
        cout << c << endl;
    }
}