//
//  Binary Indexed Tree(BIT)
//
/*

    区間和クエリと一点加算　O(logN)
    転倒数（バブルソート）
    0-indexd 実装なので配列の最小値が1の時はデクリメント
    転倒数について
    URL　https://bit.ly/2PRlQcA

*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
#define all(x) (x).begin(), (x).end()
using ll = long long;
using P = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vi>;

// 0-indexed
struct BIT{
public:
    int n;
    vector<ll> a;
    BIT(int n_):n(n_),a(n+1,0){}

    void add(int idx, ll x){
        idx++;
        if(idx<=0 || n<idx){
            cerr << "Index error" << endl;
            return;
        }
        for(int i=idx; i<=n; i+=i&(-i)){
            a[i]+=x;
        }
    }

    ll RangeSum(int idx){
        ll res = 0;
        idx++;
        if(idx<0 || n<idx){
            cerr << "Index error" << endl;
            return 0;
        }
        if(idx==0) return 0;
        for(int i=idx; i>0; i-=(i&-i)){
            res+=a[i];
        }
        return res;
    }

    ll RangeSum(int le, int ri){
        return RangeSum(ri)-RangeSum(le-1);
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vi a(n);
    rep(i,n) {cin >> a[i]; a[i]--;}

    BIT bit(n);
    ll ans = 0;
    rep(i,n){
        ans+=bit.RangeSum(n-1)-bit.RangeSum(a[i]);
        bit.add(a[i],1);
    }
    //rep(i,n-1) cout << bit.RangeSum(i,i+1) << endl;
    cout << ans << endl;
}