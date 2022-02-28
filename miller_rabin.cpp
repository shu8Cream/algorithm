//
//  ミラーラビン素数判定法
//
/*

    高速に素数判定を行う、乱択アルゴリズム
    2^64までの数であれば、確実に判定可能
    計算量 O((logn)^3) とにかく高速

*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
#define rrep(i,n) for (int i=(n-1); i>=0; i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) int((x).size())
using ll = long long;
using ull = unsigned long long;
using P = pair<ll,ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
const ll INF = 8e18;

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

struct Miller_Rabin{
    using i128 = __int128_t;
    const vi v32 = {2,7,61};
    const vi v64 = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    
    template <class T>
    T mod_pow(T a, ll b, T n){
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

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    Miller_Rabin mr;
    int n; cin >> n;
    vector<ull> x(n); rep(i,n) cin >> x[i];
    rep(i,n){
        cout << x[i] << " " << (mr.check(x[i]) ? 1:0) << endl;
    }
}