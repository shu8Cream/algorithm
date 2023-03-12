/**
*    author:  shu8Cream
*    created: 12.03.2023 01:09:40
**/

#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
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

const int mod = 1000000007;
//const int mod = 998244353;
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

    mint inv() const { return pow(mod-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}

    bool operator==(const mint &other) const {
        return x == other.x;
    }
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

template<typename T>
struct mat{
    // 初期化
    vv<T> m;
    mat():m(vv<T>()){}
    mat(int h, int w):m(vv<T>(h,vc<T>(w))){}

    vc<T> operator[](const int i) const {return m[i];}
    vc<T>& operator[](const int i) {return m[i];}

    int h = m.size();
    int w = m[0].size();

    // 基本演算
    mat& operator=(const mat& a){return *a;}
    mat& operator+=(const mat& a) {
        assert(h==a.h && w==a.w);
        rep(i,h)rep(j,w) m[i][j]+=a[i][j]; return *this;
    }
    mat& operator-=(const mat& a) {
        assert(h==a.h && w==a.w);
        rep(i,h)rep(j,w) m[i][j]-=a[i][j]; return *this;
    }
    mat& operator*=(const mat& a) {
        assert(w==a.h); mat<T> m2(h,a.w);
        rep(i,h)rep(j,a.w)rep(k,w) m2[i][j]+=m[i][k]*a[k][j];
        w=a.w; rep(i,h) m[i].resize(w);
        rep(i,h)rep(j,w) m[i][j]=m2[i][j]; return *this;
    }
    mat operator+(const mat& a) const {return mat(*this)+=a;}
    mat operator-(const mat& a) const {return mat(*this)-=a;}
    mat operator*(const mat& a) const {return mat(*this)*=a;}
    bool operator==(const mat& a){
        assert(h==a.h && w==a.w);
        rep(i,h)rep(j,w) if(m[i][j]!=a[i][j]) return false;
        return true;
    }
    // スカラ演算
    mat& operator+=(const T& a){rep(i,h)rep(j,w)m[i][j]+=a; return *this;}
    mat& operator-=(const T& a){rep(i,h)rep(j,w)m[i][j]-=a; return *this;}
    mat& operator*=(const T& a){rep(i,h)rep(j,w)m[i][j]*=a; return *this;}
    mat& operator/=(const T& a){rep(i,h)rep(j,w)m[i][j]/=a; return *this;}
    mat operator+(const T& a) const {return mat(*this)+=a;}
    mat operator-(const T& a) const {return mat(*this)-=a;}
    mat operator*(const T& a) const {return mat(*this)*=a;}
    mat operator/(const T& a) const {return mat(*this)/=a;}

    mat pow(ll t) const {
        assert(h==w);
        mat a = *this, r(h,w);
        rep(i,h) r[i][i]=1;
        while(t){
            if(t&1) r *= a;
            a *= a;
            t >>= 1;
        }
        return r;
    }
    // 転置（必要になったら追加）

    // 出力
    void show(){
        rep(i,h)rep(j,w) cerr << m[i][j] << (j+1==w?'\n':'\t');
        return;
    }
};

void Fibonacci(){
    ll n; cin >> n;
    mat<mint> m(2,2);
    m[0][0]=m[0][1]=m[1][0]=1;
    mat ans = m.pow(n);
    // cout<<ans[0][0]<<endl; // n=0が1の時
    cout<<ans[1][0]<<endl; // n=0が0の時
}

void Fibonacci_Hard(){
    using modint = atcoder::modint;
    ll n; cin >> n;
    modint::set_mod(1000000000);
    mat<modint> m(2,2);
    m[0][0]=m[0][1]=m[1][0]=1;
    mat ans = m.pow(n);
    cout<<ans[1][0].val()<<endl;
}

void ABC293E(){
    ll a,x,MOD; cin >> a >> x >> MOD;
    using modint = atcoder::modint;
    modint::set_mod(MOD);
    mat<modint> m(2,2);
    m[0][0] = a;
    m[0][1] = m[1][1] = 1;
    mat t = m.pow(x);
    mat<modint> b(2,1);
    b[1][0] = 1;
    mat ans = t*b;
    cout<<ans[0][0].val()<<endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // Fibonacci();
    // Fibonacci_Hard();
    ABC293E();
}
