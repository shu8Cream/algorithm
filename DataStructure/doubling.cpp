/**
 * @file doubling.cpp
 * @author shu8Cream
 * @brief 
 * @version 0.1
 * @date 2022-07-17
 * 
 * @verify https://atcoder.jp/contests/abc258/tasks/abc258_e
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

struct DoublingTable{
    vvi table;
    vi pack;
    const int MX = 60;
    DoublingTable(vi arr, ll x){
        int n = sz(arr);
        table.resize(MX);
        rep(i,MX) table[i].resize(n);
        // テーブルの定義 ここから
        // table[0][i]を埋める
        ll sum = reduce(all(arr));
        vi rarr(2*n);
        rep(i,2*n) rarr[i+1] = rarr[i] + arr[i%n];
        pack.resize(n);
        rep(i,n){
            ll cnt = 0;
            if(x>=sum){
                ll ti = x/sum;
                cnt += n*ti;
            }
            ll rx = x%sum;
            int id = lower_bound(all(rarr),rx+rarr[i]) - rarr.begin();
            cnt+=id-i;
            pack[i] = cnt;
            table[0][i] = id%n;
        }
        // ここまで
        rep(k,MX-1)rep(i,n){
            table[k+1][i] = table[k][table[k][i]];
        }
    }
    void debug_view(){
        rep(i,sz(table)) cerr << table[i] << endl;
    }
    ll query(ll x){
        int n = sz(table[0]);
        ll now = 0;
        rep(i,MX)if(x>>i&1) now = table[i][now];
        return pack[now];
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ll n,q,x; cin >> n >> q >> x;
    vi w(n); cin >> w;
    DoublingTable db(w,x);
    rep(qi,q){
        ll k; cin >> k;
        cout << db.query(k-1) << endl;
    }
}