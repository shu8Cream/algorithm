/**
*    author:  shu8Cream
*    created: 10.02.2023 16:55:34
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

// N点の座標から、N本の候補辺を列挙する（重み、頂点１、頂点２）
template<typename T>
vector<tuple<T,T,T>> manhattan_mst(vc<T> xs, vc<T> ys){
    vector<tuple<T,T,T>> res;
    int n = sz(xs);
    vc<int> ids(n); iota(all(ids),0);
    rep(s,2){
        rep(t,2){
            sort(all(ids), [&](int &a, int &b){
                return xs[a]+ys[a] < xs[b]+ys[b]; // 45度回転後のY座標に対して走査
            });
            map<T,T> sweep;
            for(int i : ids){
                for(auto it=sweep.lower_bound(-ys[i]); it!=sweep.end(); it=sweep.erase(it)){
                    int j = it->second;
                    if(xs[i]-ys[i] < xs[j]-ys[j]) break;
                    res.emplace_back(abs(xs[i]-xs[j])+abs(ys[i]-ys[j]), i, j);
                }
                sweep[-ys[i]] = i;
            }
            swap(xs,ys); // R1->R2
        }
        for(auto &x:xs) x = -x; // R1->R8
    }
    sort(all(res));
    return res;
}

struct UnionFind{
    vector<int> par;
    UnionFind(){}
    UnionFind(int n=0): par(n, -1){}
    int find(int x){
        if(par[x] < 0) return x;
        return par[x] = find(par[x]);
    }
    bool merge(int x, int y){
        x = find(x); y = find(y);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x,y); //マージテク
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    bool same(int x, int y) {return find(x) == find(y);}
    int size(int x) {return -par[find(x)];}
};

void YOSUPO(){
    ll n; cin >> n;
    vi x(n),y(n);
    rep(i,n) cin >> x[i] >> y[i];

    ll weight = 0;
    vc<P> edges;
    UnionFind uf(n);
    for(auto[w,i,j] : manhattan_mst(x,y)){
        if(!uf.same(i,j)){
            weight += w;
            edges.emplace_back(i,j);
            uf.merge(i,j);
        }
    }
    cout<<weight<<endl;
    for(auto[a,b]:edges) cout<<a<<" "<<b<<endl;
}

void ABC283F(){
    ll n; cin >> n;
    vi p(n); cin >> p;
    vi q(n); iota(all(q),1);

    vc<tuple<ll,ll,ll>> edges;
    UnionFind uf(n);
    for(auto[w,i,j] : manhattan_mst(p,q)){
        if(!uf.same(i,j)){
            edges.emplace_back(w,i,j);
            uf.merge(i,j);
        }
    }
    vi ans(n,LINF);
    for(auto[w,a,b]:edges){
        chmin(ans[a],w);
        chmin(ans[b],w);
    }
    cout<<ans<<endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    // YOSUPO();
    ABC283F();
}
