//
//  偏角ソート
//
/*

    verify: ABC225(https://atcoder.jp/contests/abc225/tasks/abc225_e)

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

bool argcmp(const P& a, const P& b) {
    bool zone1 = a.second > 0 || (a.second==0 && a.first>=0);
    bool zone2 = b.second > 0 || (b.second==0 && b.first>=0);
    if(zone1 != zone2) return zone1;
    ll cross = a.first*b.second - a.second*b.first;
    if(cross==0) return abs(a.first+a.second) - abs(b.first+b.second);
    return cross>0;  
}

double length(P a){
    return sqrt(a.first*a.first + a.second*a.second);
}

double angle(P p1, P p2){
    double dot = p1.first*p2.first + p1.second*p2.second;
    dot /= length(p1) * length(p2); 
    return acos(dot) / M_PI * 180.0;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n; cin >> n;
    vi x(n),y(n);
    rep(i,n) cin >> x[i] >> y[i];
    double ans = 0.0;
    rep(i,n){
        int tx = x[i], ty = y[i];
        vector<P> vertex;
        rep(j,n){
            if(i==j) continue;
            int nx = x[j]-tx, ny = y[j]-ty;
            vertex.push_back({nx,ny});
        }
        sort(all(vertex),argcmp);
        debug(vertex);
        int r = 0;
        
        rep(l,n-1){
            while(angle(vertex[l],vertex[r])<angle(vertex[l],vertex[(r+1)%(n-1)]))
                r = (r+1)%(n-1);
            chmax(ans, angle(vertex[l],vertex[r]));
        }
    }
    printf("%.15lf\n",ans);
}