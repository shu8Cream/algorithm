/**
 * @file BIT.cpp
 * @author shu8Cream
 * @brief Binary Indexed Tree(BIT)
 * @version 0.1
 * @date 2022-04-09
 * 
 * @note 
 *  区間和クエリと一点加算　O(logN)
 *  転倒数（バブルソート）
 *  0-indexd 実装なので配列の最小値が1の時はデクリメント
 *  転倒数について
 *  URL https://bit.ly/2PRlQcA
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
/** Binary Indexed Tree
 * @note 内部では1-indexed, 外部からは0-indexedで扱う
 * 
 * メンバ変数
 * @param int-n 木のサイズ
 * @param vector<T>-a 値を持つ配列
 * 
 * コンストラクタ
 * @param[in] int 木のサイズを受け取る
 * 
 * メンバ関数
 * @def void add インデックスで値を加える
 *  @param[in] int-idx インデックス
 *  @param[in] T-x 加える値
 *  @assert [0,n)外のidxを指定する
 * 
 * @def T sum 範囲を指定して合計を返す
 *  @param[in] int-idx 範囲の終わりを指定
 *  @param[out] T-res 0-idxまでの区間の合計
 *  @assert [0,n]外のidxを指定する
 * 
 * @def T sum 範囲を指定して合計を返す
 *  @param[in] int-l 範囲の始まりを指定
 *  @param[in] int-r 範囲の終わりを指定
 *  @param[out] T-res 0-idxまでの区間の合計
 *  @ref sum "0からidxまでの合計を返す"
 * 
 */
template<typename T>
struct BIT{
public:
    int n; vector<T> a;
    BIT(int n_):n(n_),a(n+1,0){}

    void add(int idx, T x){
        idx++;
        assert(0<idx && idx<=n && "Index error");
        for(int i=idx; i<=n; i+=i&(-i)){
            a[i]+=x;
        }
    }

    T sum(int idx){
        T res = 0;
        idx++;
        assert(0<=idx && idx<=n && "Index error");
        if(idx==0) return 0;
        for(int i=idx; i>0; i-=(i&-i)){
            res+=a[i];
        }
        return res;
    }

    T sum(int l, int r){
        if(l==0) return sum(r-1);
        return sum(r-1)-sum(l-1);
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vi a(n);
    rep(i,n) {cin >> a[i]; a[i]--;}

    BIT<int> bit(n);
    ll ans = 0;
    rep(i,n){
        ans+=bit.sum(n-1)-bit.sum(a[i]);
        bit.add(a[i],1);
    }
    //rep(i,n-1) cout << bit.sum(i,i+1) << endl;
    cout << ans << endl;
}
