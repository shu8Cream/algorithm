/**
*    author:  shu8Cream
*    created: 05.03.2023 14:19:54
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

using PP = pair<int,P>;

constexpr int DR[4] = {1,0,-1,0};
constexpr int DC[4] = {0,1,0,-1};
const string direction = "DRUL";

int H,W; 
int a[55][55];
P pre[55][55]; // 経路復元

bool out_of_grid(int y, int x){
    if(y<0 || y>=H || x<0 || x>=W) return true;
    return false;
}

void dijkstra(int sy, int sx, vvi &dist){
    dist[sy][sx] = 0;
    priority_queue<PP, vector<PP>, greater<PP>> q;
    q.emplace(PP(0,P(sy,sx)));
    while(sz(q)){
        auto[nowD,pos] = q.top(); q.pop();
        auto[y,x] = pos;
        rep(v,4){
            int ny = y+DR[v], nx = x+DC[v];
            if(out_of_grid(ny,nx)) continue;
            if(dist[ny][nx]>a[ny][nx] + nowD){
                dist[ny][nx] = a[ny][nx] + nowD;
                pre[ny][nx] = P(y,x);
                q.emplace(PP(dist[ny][nx],P(ny,nx)));
            }
        }
    }
}

vc<P> restore(int ty, int tx){
    vc<P> res;
    int ny,nx;
    do{
        res.emplace_back(ty,tx);
        ny = ty, nx = tx;
        tie(ty,tx) = pre[ny][nx];
    }while(ty!=-1||tx!=-1);
    reverse(all(res));
    return res;
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    cin >> H >> W;
    rep(i,H)rep(j,W) cin >> a[i][j];
    vvi dist(H,vi(W,INF));
    vvi dist2(H,vi(W,INF));
    vvi dist3(H,vi(W,INF));

    dijkstra(H-1,0,dist);
    dijkstra(H-1,W-1,dist2);
    dijkstra(0,W-1,dist3);

    {
        rep(i,H){
            rep(j,W) cerr<<dist[i][j]<<"\t";
            cerr<<endl;
        }
        cerr<<"------"<<endl;
        rep(i,H){
            rep(j,W) cerr<<dist2[i][j]<<"\t";
            cerr<<endl;
        }
        cerr<<"------"<<endl;
        rep(i,H){
            rep(j,W) cerr<<dist3[i][j]<<"\t";
            cerr<<endl;
        }
    }

    ll ans = LINF;
    rep(y,H)rep(x,W){
        chmin(ans, dist[y][x]+dist2[y][x]+dist3[y][x]-a[y][x]*2);
    }
    cout<<ans<<endl;
}
