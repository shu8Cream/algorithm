/**
 * @file random_generator.cpp
 * @author shu8Cream
 * @brief 
 * @version 0.1
 * @date 2022-11-03
 * 
 * 
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
const int INF = 1e9;
const ll LINF = 8e18;
template<typename T>istream& operator>>(istream&i,vc<T>&v){rep(j,sz(v))i>>v[j];return i;}
template<typename T>string join(const T&v,const string& d=""){stringstream s;rep(i,sz(v))(i?s<<d:s)<<v[i];return s.str();}
template<typename T>ostream& operator<<(ostream&o,const vc<T>&v){if(sz(v))o<<join(v," ");return o;}
template<typename T1,typename T2>istream& operator>>(istream&i,pair<T1,T2>&v){return i>>v.first>>v.second;}
template<typename T1,typename T2>ostream& operator<<(ostream&o,const pair<T1,T2>&v){return o<<v.first<<","<<v.second;}
template<class T> inline bool chmax(T& a, T b) {if(a<b) { a=b;return true; } return false;}
template<class T> inline bool chmin(T& a, T b) {if(a>b) { a=b;return true; } return false;}

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

struct RandomGenerator {
    mt19937_64 engine;
    uniform_int_distribution<> dist = uniform_int_distribution<>(0, INT_MAX);

    RandomGenerator() {
        random_device seed_gen;
        engine = mt19937_64(seed_gen());
    }

    RandomGenerator(int seed) {
        engine = mt19937_64(seed);
    }

    double uniform(double l=0.0, double r=1.0) {
        assert(l <= r);
        return l + (r-l)*dist(engine)/INT_MAX;
    }

    // [l,r)の範囲で値を返す
    int randrange(int l, int r) {
        assert(l < r);
        return l + dist(engine)%(r-l);
    }

    template <class T>
    T choice(const vc<T> &data) {
        return data.at(randrange(0, sz(data)));
    }

    // [l,r)の範囲からk個抽出
    vc<int> sampling(int l, int r, int k) {
        assert(0<k && k<=r-l);
        vc<int> ret;
        while(sz(ret) < k){
            int x = randrange(l, r);
            if(find(all(ret),x)==ret.end()) ret.push_back(x);
        }
        sort(all(ret));
        return ret;
    }

    template <class T>
    void shuffle_vector(vc<T> &data) {
        shuffle(all(data), engine);
    }
};

RandomGenerator generator;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    rep(i,100) cout << generator.randrange(0,10) << " ";
    cout << endl;
    cout << generator.sampling(0,100,20) << endl;
}
