//
//  有理数クラス（誤差評価が厳しい時に）
//
/*

    b/aとして、約分を自動で行う。分母0も許容。

*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
#define rrep(i,n) for (int i=(n-1); i>=0; i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) int((x).size())
using ll = long long;
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

void debug_out() { cout << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
cout << H << " ";
debug_out(T...);
}

#ifdef _DEBUG
#define debug(...) debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// fraction: 分数の略
// b/aの想定
struct frac{
    ll a,b;
    frac(ll _a=1,ll _b=0) : a(_a),b(_b) {
        if(a==0) {b = 1; return;}
        if(a<0) a = -a, b = -b;
        ll g = gcd(a,b);
        a/=g; b/=g;
    }
    bool operator<(const frac &other) const {
        return b*other.a < a*other.b;
    }
    bool operator==(const frac &other) const {
        return b*other.a == a*other.b;
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n; cin >> n;
    vi x(n),y(n);
    rep(i,n) cin >> x[i] >> y[i];
    using PF = pair<frac,frac>;
    vector<PF> fus(n);
    rep(i,n){
        frac rf = frac(x[i]-1,y[i]); 
        frac lf = frac(x[i],y[i]-1); 
        fus[i] = {rf,lf};
    }
    sort(all(fus));
    rep(i,n) auto [rf, lf] = fus[i];
    ll ans = 0;
    frac cur = frac(1,0);
    rep(i,n){
        auto [rf,lf] = fus[i];
        if(lf<cur) continue;
        cur = rf;
        ans++;
    }
    cout << ans << endl;
}