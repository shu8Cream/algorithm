//
//  Mo's Algorithm
//
/*

    使用できる条件
    1. 配列の要素が不変
    2. クエリを先読みできる(オフライン)
    3. 区間[l,r)の結果から区間 [l+1,r), [l−1,r), [l,r−1), [l,r+1) の結果を容易に計算できる

    計算量 O((N+Q)√N*K) (Qはクエリ数、Kは範囲の伸縮一回にかかる計算量)
    verify: Range Pairing Query (https://atcoder.jp/contests/abc242/tasks/abc242_g)

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

const int MAX_VAL = 500500;
int a[MAX_VAL];     //要素
int cnt[MAX_VAL];   //区間内のiの個数
int res;            //区間内の種類の数
 
class Mo{
private:
    vector<int> left, right;
    const int width;
    void add(const int id);
    void del(const int id);
 
public:
    vector<int> ans;
 
    Mo(const int n) : width((int)sqrt(n)){}
    // クエリ[l,r)
    void insert(const int l, const int r){
        left.push_back(l), right.push_back(r);
    }
    void solve(){
        const int sz = (int)left.size();
        int nl = 0, nr = 0;
        vector<int> ord(sz);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](const int a, const int b){
            const int c = left[a] / width, d = left[b] / width;
            return (c == d) ? ((c & 1) ? (right[b] < right[a]) : (right[a] < right[b])) : (c < d);
        });
        ans.resize(sz);
        for(const int id : ord){
            while(nl > left[id]) add(--nl);
            while(nr < right[id]) add(nr++);  //add
            while(nl < left[id]) del(nl++);
            while(nr > right[id]) del(--nr);  //del
            ans[id] = res;
        }
    }
};
 
//idは元の配列のインデックス
void Mo::add(const int id){
    res -= cnt[a[id]]/2;
    ++cnt[a[id]];
    res += cnt[a[id]]/2;
}
 
void Mo::del(const int id){
    res -= cnt[a[id]]/2;
    --cnt[a[id]];
    res += cnt[a[id]]/2;
}
 
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n, q, l, r;
    cin >> n;
    Mo mo(n);
    rep(i,n) cin >> a[i];
    cin >> q;
    rep(i,q){
        cin >> l >> r;
        --l, mo.insert(l, r);
    }
    mo.solve();
    const auto& ans = mo.ans;
    rep(i,q) cout << ans[i] << "\n";
    return 0;
}