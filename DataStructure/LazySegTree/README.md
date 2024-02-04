# 遅延評価SegmentTree

## 実装
- [LazySegTree]()

## 定義が必要なもの
`S`: モノイドの型
`F`: 作用の型
`S op(S a, S b)`: 二項演算
`S e()`: 二項演算の単位元
`S mapping(F f, S x)`: Sに対する作用を表す関数
`F composition(F f, F g)`: 作用と作用の合成関数 f(g(x))
`F id()`: 作用の単位元

## ACL LazySegTree チートシート
- [AtCoder LibraryのLazy Segtreeのチートシート](https://betrue12.hateblo.jp/entry/2020/09/23/005940)
#### 区間加算・区間最小
```cpp
using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return min(a, b); }
S e(){ return INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

int main(){
    int N;
    vector<S> a(N);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
}
```

#### 区間加算・区間最大
```cpp
using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

int main(){
    int N;
    vector<S> a(N);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
}
```

#### 区間加算・区間和
```cpp
struct S{
    long long value;
    int size;
};
using F = long long;

S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S x){ return {x.value + f*x.size, x.size}; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

int main(){
    int N;
    vector<S> a(N, {0, 1});
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
}
```

#### 区間更新・区間最小
```cpp
using S = long long;
using F = long long;

const S INF = 8e18;
const F ID = 8e18;

S op(S a, S b){ return min(a, b); }
S e(){ return INF; }
S mapping(F f, S x){ return (f == ID ? x : f); }
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }

int main(){
    int N;
    vector<S> a(N);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
}
```

#### 区間更新・区間最大
```cpp
using S = long long;
using F = long long;

const S INF = 8e18;
const F ID = 8e18;

S op(S a, S b){ return max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return (f == ID ? x : f); }
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }

int main(){
    int N;
    vector<S> a(N);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
}
```

#### 区間更新・区間和
```cpp
struct S{
    long long value;
    int size;
};
using F = long long;

const F ID = 8e18;

S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S x){
    if(f != ID) x.value = f*x.size;
    return x;
}
F composition(F f, F g){ return (f == ID ? g : f); }
F id(){ return ID; }

int main(){
    int N;
    vector<S> a(N, {0, 1});
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
}
```

#### 区間ax+b・区間和
```cpp
using mint = modint998244353;

struct S {
    mint a;
    int size;
};
struct F { // ax + b
    mint a, b;
};

S op(S l, S r) { return S{l.a + r.a, l.size + r.size}; }
S e() { return S{0, 0}; }
S mapping(F l, S r) { return S{r.a * l.a + r.size * l.b, r.size}; }
F composition(F l, F r) { return F{r.a * l.a, r.b * l.a + l.b}; }
F id() { return F{1, 0}; }

int main(){
    int N;
    vector<S> a(N);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
    for(int i=0; i<n; i++) seg.set(i,{a[i],1});
}
```

#### 区間等差数列更新・区間最大
- [区間に等差数列を作用させる遅延セグメントツリー](https://null-mn.hatenablog.com/entry/2021/08/22/064325)
```cpp
using S = long long;
struct S {
    long long v;
    int l, r;
};
struct F {
    long long a,b;
};

const S INF = 8e18;

S op(S a, S b){ return {max(a.v, b.v), min(a.l, b.l), max(a.r, b.r)}; }
S e(){ return {-INF,-INF,INF}; }
S mapping(F f, S x){
    if(f.a>=0) return { f.a * (x.r - 1) + f.b, x.l, x.r };
    else return { f.a * x.l + f.b, x.l, x.r };
}
F composition(F f, F g){ return f.a == INF ? g : f; }
F id(){ return {INF, INF}; }

int main(){
    int N;
    vector<int> a(N);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(N);
}
```

#### 区間等差数列更新・区間最小
```cpp
using S = long long;
struct S {
    long long v;
    int l, r;
};
struct F {
    long long a,b;
};

const S INF = 8e18;

S op(S a, S b){ return {min(a.v, b.v), min(a.l, b.l), max(a.r, b.r)}; }
S e(){ return {INF,-INF,INF}; }
S mapping(F f, S x){
    if(f.a>=0) return { f.a * x.l + f.b, x.l, x.r };
    else return { f.a * (x.r - 1) + f.b, x.l, x.r };
}
F composition(F f, F g){ return f.a == INF ? g : f; }
F id(){ return {INF, INF}; }

int main(){
    int N;
    vector<S> a(N);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
}
```

#### 区間等差数列更新・区間和
```cpp
using S = long long;
struct S {
    long long v;
    int l, r; // [l,r)
};
struct F {
    long long a,b;
};

const S INF = 8e18;

S op(S a, S b){ return {a.v+b.v, min(a.l, b.l), max(a.r, b.r)}; }
S e(){ return {0,-INF,INF}; }
S mapping(F f, S x){
    return { ((x.r-x.l)*f.a+f.b*2)*(x.r-x.l)/2, x.l, x.r };
}
F composition(F f, F g){ return f.a == INF ? g : f; }
F id(){ return {INF, INF}; }

int main(){
    int N;
    vector<S> a(N);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
}
```

#### 区間等差数列加算・区間和
```cpp
using S = long long;
struct S {
    long long v;
    int l, r; // [l,r)
};
struct F {
    long long a,b;
};

const S INF = 8e18;

S op(S a, S b){ return {a.v+b.v, min(a.l, b.l), max(a.r, b.r)}; }
S e(){ return {0,-INF,INF}; }
S mapping(F f, S x){
    return { x.v + ((x.r-x.l)*f.a+f.b*2)*(x.r-x.l)/2, x.l, x.r };
}
F composition(F f, F g){ return f.a == INF ? g : f; }
F id(){ return {INF, INF}; }

int main(){
    int N;
    vector<S> a(N);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
}
```
