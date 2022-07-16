//
//  Binary Trie
//
/**

 *  できること　いずれも計算量　log(maxA)
    insert()
    erase()
    max_element() 最大値取得
    min_element() 最小値取得
    lower_bound()
    upper_bound()
    kth_element(k) k番目に小さい値の取得
    max_element(x) xでXORした時の最大値取得
    min_element(x) xでXORした時の最小値取得
    kth_element(k,x) xでXORした時のk番目に小さい値の取得

 * https://judge.yosupo.jp/submission/84364

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

template<typename U = unsigned, int B = 32>
struct BinaryTrie{
private:
    struct node{
        int cnt;
        node *left,*right;
        node() : cnt(0), left(nullptr), right(nullptr) {}
    };
    node* add(node* t, U val, int d = B-1){
        if(!t) t = new node();
        t->cnt += 1;
        if(d<0) return t;
        bool f = (val>>(U)d) & (U)1;
        if(f) t->right = add(t->right, val, d-1);
        else t->left = add(t->left, val, d-1);
        return t;
    }
    node* sub(node* t, U val, int d = B-1){
        assert(t);
        t->cnt -= 1;
        if(t->cnt==0) return nullptr;
        if(d<0) return t;
        bool f = (val>>(U)d) & (U)1;
        if(f) t->right = sub(t->right,val,d-1);
        else t->left = sub(t->left,val,d-1);
        return t;
    }
    U get(node* t, int id, int d = B-1) const {
        if(d<0) return 0;
        int m = t->left ? t->left->cnt : 0;
        return id < m ? get(t->left, id, d-1) : get(t->right, id-m, d-1) | ((U)1<<(U)d);
    }
    U get_min(node* t, U val, int d = B-1) const {
        assert(t);
        if(d<0) return 0;
        bool f = (val>>(U)d) & (U)1;
        if(f) f ^= !t->right;
        else f ^= !t->left;
        if(f) return get_min(t->right, val, d-1) | ((U)f<<(U)d); 
        else return get_min(t->left, val, d-1) | ((U)f<<(U)d); 
    }
    int count_lower(node* t, U val, int d = B-1) {
        if (!t || d < 0) return 0;
        bool f = (val >> (U)d) & (U)1;
        if(f) return (f && t->left ? t->left->cnt : 0) + count_lower(t->right, val, d-1);
        else return (f && t->left ? t->left->cnt : 0) + count_lower(t->left, val, d-1);
    }

    node *root;
public:
    BinaryTrie() : root(nullptr) {}
    
    int size() const {
        return root ? root->cnt : 0;
    }
    bool empty() const {
        return !root;
    }
    int count(U val) const {
        if(!root) return 0;
        node* t = root;
        rrep(i,B){
            bool f = (val>>(U)i) & (U)1;
            if(f) t = t->right;
            else t = t->left;
            if(!t) return 0;
        }
        return t->cnt;
    }
    void insert(U val) {
        root = add(root, val);
    }
    void erase(U val) {
        root = sub(root, val);
    }
    U operator[](int id) const {
        assert(0<=id && id<size());
        return get(root, id);
    }
    U max_element(U bias = 0) const {
        return get_min(root, ~bias);
    }
    U min_element(U bias = 0) const {
        return get_min(root, bias);
    }
    int lower_bound(U val) { // return idx
        return count_lower(root, val);
    }
    int upper_bound(U val) { // return idx
        return count_lower(root, val + 1);
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    BinaryTrie bt;
    int q; cin >> q;
    int c,x;
    rep(qi,q){
        cin >> c >> x;
        if(c==0){
            if(!bt.count(x)) bt.insert(x);
        }else if(c==1){
            if(bt.count(x)) bt.erase(x);
        }else{
            int a = bt.min_element(x);
            cout << (a^x) << endl;
        }
    }
}