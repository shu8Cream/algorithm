//
//  スプレー木（Splay Tree）
//
/*

    計算量
    検索・追加・削除　logN (amortized)

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

struct SplayNode{
    SplayNode *left,*right,*parent;
    int size,value;
    
    SplayNode(){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        size = 1;
    }

    void rotate(){
        SplayNode *pp,*p,*b;
        p = this->parent;
        pp = p->parent;

        if(p->left == this){
            b = this->right;
            this->right = p;
            p->left = b;
        }else{
            b = this->left;
            this->left = p;
            p->right = b;
        }
        if(pp && pp->left==p) pp->left = this;
        if(pp && pp->right==p) pp->right = this;
        this->parent = pp;
        p->parent = this;
        
        if(b) b->parent = p;

        p->update();
        this->update();
    }
    int state(){
        if(!this->parent) return 0;
        if(this->parent->left == this) return 1;
        if(this->parent->right == this) return -1;
        return 0;
    }
    void splay(){
        while(this->state()){
            if(this->parent->state()==0) this->rotate();
            else if(this->state() == this->parent->state()){
                this->parent->rotate();
                this->rotate();
            }else{
                this->rotate();
                this->rotate();
            }
        }
    }
    void update(){
        this->size = 1;
        if(this->left) this->size+=this->left->size;
        if(this->right) this->size+=this->right->size;
    }
};

SplayNode *get(int idx, SplayNode *root){
    SplayNode *now = root;
    while(1){
        int lsize = now->left ? now->left->size : 0;
        if(idx<lsize){
            now = now->left;
        }
        if(idx==lsize){
            now->splay();
            return now;
        }
        if(idx>lsize){
            now = now->right;
            idx = idx-lsize-1;
        }
    }
}

SplayNode node[200200];

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int q; cin >> q;
    int vecsize = 0;
    rep(i,q){
        node[i].parent = &node[i+1];
        node[i+1].left = &node[i];
        node[i+1].update();
    }
    SplayNode *root = &node[q];
    rep(i,q){
        int c; cin >> c;
        if(c==0){
            int x; cin >> x;
            root = get(vecsize++,root);
            root->value = x;
        }
        if(c==1){
            int x; cin >> x;
            root = get(x,root);
            cout << root->value << endl;
        }
        if(c==2){
            vecsize--;
        }
    }
}