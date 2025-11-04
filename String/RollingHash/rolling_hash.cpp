/**
*    author:  shu8Cream
*    created: 08.01.2023 01:07:26
*
*    下記を改良
*    https://ei1333.github.io/luzhiled/snippets/string/rolling-hash.html
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct RollingHash {
    using ll = long long;
    using ull = unsigned long long;
    ull mod;
    ull base;
    vector<ull> hashed, power;

    static constexpr ull mask(ll x){ return (1ULL << x) - 1; }

    template<class T>
    inline ull safe_mod(T x) {
        /*
        // mod = 2^61-1以外のとき
        x %= mod;
        /*/
        x = (x >> 61) + (x & ((1ULL << 61) - 1));
        if(x > mod) {
            x -= mod;
        }
        //*/
        return x;
    }

    inline ull mul(ull a, ull b) {
        // /*
        // int128が使えるならこっち
        __uint128_t res = __uint128_t(a) * b;
        /*/
        ull au = a>>31, bu = b>>31;
        ull ad = a & mask(31), bd = b & mask(31);
        ull m = ad * bu + bd * au;
        ull mu = m>>30;
        ull md = m & mask(30);
        ull res = au * bu * 2 + mu + (md<<31) + ad * bd;
        //*/
        return safe_mod(res);
    }

    RollingHash(const string &s, ull mod=(1ULL<<61) - 1): mod(mod) {
        std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<ull> rand(1,mod-1);
        base = rand(mt);
        int n = s.size();
        hashed.assign(n + 1, 0);
        power.assign(n + 1, 0);
        power[0] = 1;
        for(int i = 0; i < n; i++) {
            power[i + 1] = mul(power[i], base);
            hashed[i + 1] = safe_mod(mul(hashed[i], base) + s[i]);
        }
    }

    ull get(ll l, ll r) {
        return safe_mod(hashed[r] + mod - mul(hashed[l], power[r - l]));
    }

    ull connect(ull h1, ull h2, unsigned int h2len) {
        return safe_mod(mul(h1, power[h2len]) + h2);
    }

    ll LCP(RollingHash &b, ll l1, ll r1, ll l2, ll r2) {
        ll len = min(r1 - l1, r2 - l2);
        ll low = -1, high = len + 1;
        while(high - low > 1) {
            ll mid = (low + high) / 2;
            if(get(l1, l1 + mid) == b.get(l2, l2 + mid)) low = mid;
            else high = mid;
        }
        return (low);
    }
};

// want to solve: https://codeforces.com/contest/1129/problem/C

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ll n; cin >> n;
    string t; cin >> t;
    string rt = t;
    reverse(rt.begin(), rt.end());
 
    string T = t+rt;
    RollingHash rh(T);
    for(int i=1; i<n; i++){
        auto h1 = rh.get(0,i);
        auto h2 = rh.get(i+n, 2*n);
        auto v1 = rh.connect(h1,h2,n-i);
        auto v2 = rh.get(3*n-i, 4*n-i);
        if(v1==v2){
            string s = rt.substr(n-i,n);
            cout << s << endl;
            cout << i << endl;
            return 0;
        }
    }
    string s = t.substr(n,n);
    reverse(s.begin(), s.end());
    if(s==t.substr(0,n)){
        cout << s << endl;
        cout << n << endl;
        return 0;
    }
    cout << -1 << endl;
}
