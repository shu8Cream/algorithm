/**
*    author:  shu8Cream
*    created: 2026/01/24 20:58:57
**/

#include <bits/stdc++.h>
using namespace std;

/**
 * Angular Sort (偏角ソート)
 * 詳細ドキュメント: AngularSort.md
 */
struct AngularSort {
    using ll = long long;
    using P = pair<ll, ll>;
    
    vector<P> dots;
    ll cx = 0, cy = 0;      // 中心点
    ll sx = 1, sy = 0;      // 始線の方向ベクトル（デフォルト: 右方向 = 0°）
    bool clockwise = false; // true: 時計回り, false: 反時計回り
    bool near_first = true; // true: 近い順, false: 遠い順
    
    // build()で構築される内部データ
    vector<int> ord_;    // ソート順
    vector<int> pos_;    // pos_[i] = 点iのソート順位
    vector<int> left_;   // left_[ソート順位] = 同一偏角グループの左端
    vector<int> right_;  // right_[ソート順位] = 同一偏角グループの右端
    bool built_ = false;
    
    AngularSort() {}
    
    void add(ll x, ll y) {
        dots.emplace_back(x, y);
        built_ = false;
    }
    
    void clear() {
        dots.clear();
        built_ = false;
    }
    
    int size() const { return dots.size(); }
    
    // 中心点を設定
    void set_center(ll x, ll y) {
        cx = x; cy = y;
        built_ = false;
    }
    
    // 始線の方向ベクトルを設定
    void set_start_axis(ll dx, ll dy) {
        sx = dx; sy = dy;
        built_ = false;
    }
    
    // 始線を角度(度)で設定 (0, 90, 180, 270 のみ対応)
    void set_start_axis_deg(int deg) {
        deg = ((deg % 360) + 360) % 360;
        if (deg == 0)        { sx = 1; sy = 0; }
        else if (deg == 90)  { sx = 0; sy = 1; }
        else if (deg == 180) { sx = -1; sy = 0; }
        else if (deg == 270) { sx = 0; sy = -1; }
        else assert(false && "Only 0, 90, 180, 270 degrees are supported");
        built_ = false;
    }
    
    // 時計回り/反時計回りを設定
    void set_clockwise(bool cw) {
        clockwise = cw;
        built_ = false;
    }
    
    // 同一偏角での距離順を設定 (true: 近い順, false: 遠い順)
    void set_near_first(bool nf) {
        near_first = nf;
        built_ = false;
    }
    
    /**
     * ソートを実行し、range()用の事前計算を行う
     * 設定を変更した後は必ず呼ぶこと
     * 計算量: O(N log N)
     */
    void build() {
        int n = dots.size();
        if (n == 0) {
            built_ = true;
            return;
        }
        
        // 相対座標と距離の2乗を事前計算
        vector<ll> rx(n), ry(n), d2(n);
        for (int i = 0; i < n; i++) {
            rx[i] = dots[i].first - cx;
            ry[i] = dots[i].second - cy;
            d2[i] = rx[i] * rx[i] + ry[i] * ry[i];
        }
        
        // 領域番号を事前計算 (0,1,2,3,4)
        // 0: 始線上（正方向）, 1: 前半, 2: 始線の逆方向, 3: 後半, 4: 中心点
        vector<int> region(n);
        for (int i = 0; i < n; i++) {
            if (rx[i] == 0 && ry[i] == 0) {
                region[i] = 4;
            } else {
                ll cr = sx * ry[i] - sy * rx[i];
                if (cr == 0) {
                    ll dt = sx * rx[i] + sy * ry[i];
                    region[i] = dt > 0 ? 0 : 2;
                } else if (!clockwise) {
                    region[i] = cr > 0 ? 1 : 3;
                } else {
                    region[i] = cr < 0 ? 1 : 3;
                }
            }
        }
        
        ord_.resize(n);
        iota(ord_.begin(), ord_.end(), 0);
        
        // 距離でソート
        std::sort(ord_.begin(), ord_.end(), [&](int i, int j) {
            if (d2[i] != d2[j]) return near_first ? (d2[i] < d2[j]) : (d2[i] > d2[j]);
            return i < j;
        });
        
        // stable_sortで偏角ソート
        std::stable_sort(ord_.begin(), ord_.end(), [&](int i, int j) {
            if (region[i] != region[j]) return region[i] < region[j];
            // 同じ領域内での比較
            if (region[i] == 0 || region[i] == 2 || region[i] == 4) return false;
            // 外積で比較
            ll cr = rx[i] * ry[j] - ry[i] * rx[j];
            if (cr == 0) return false;
            return clockwise ? (cr < 0) : (cr > 0);
        });
        
        // 各点のソート順位
        pos_.resize(n);
        for (int i = 0; i < n; i++) {
            pos_[ord_[i]] = i;
        }
        
        // 同一偏角グループの左端・右端
        // 同一偏角 = 同じ領域 かつ 外積が0
        left_.resize(n);
        right_.resize(n);
        iota(left_.begin(), left_.end(), 0);
        iota(right_.begin(), right_.end(), 0);
        
        for (int k = 1; k < n; k++) {
            int i = ord_[k], j = ord_[k - 1];
            // 同一偏角の判定: 同じ領域 かつ 外積=0
            if (region[i] == region[j]) {
                ll cr = rx[i] * ry[j] - ry[i] * rx[j];
                if (cr == 0) {
                    left_[k] = left_[k - 1];
                }
            }
        }
        for (int k = n - 2; k >= 0; k--) {
            int i = ord_[k], j = ord_[k + 1];
            if (region[i] == region[j]) {
                ll cr = rx[i] * ry[j] - ry[i] * rx[j];
                if (cr == 0) {
                    right_[k] = right_[k + 1];
                }
            }
        }
        
        built_ = true;
    }
    
    // ソート順のインデックス列を取得
    const vector<int>& get_order() const {
        assert(built_ && "Call build() first");
        return ord_;
    }
    
    // 点iのソート順位を取得
    int get_pos(int i) const {
        assert(built_ && "Call build() first");
        return pos_[i];
    }
    
    /**
     * 頂点from_idから頂点to_idまでの範囲にある頂点IDを返す
     * （ソート順で from_id → to_id の方向に進む）
     * 
     * 同一偏角の点はすべて含める
     * 
     * @param from_id 開始頂点のID（dots配列のインデックス）
     * @param to_id 終了頂点のID（dots配列のインデックス）
     * @return 範囲内の頂点IDのvector（ソート順）
     * 
     * 計算量: O(K) (K = 結果サイズ)
     */
    vector<int> range(int from_id, int to_id) const {
        assert(built_ && "Call build() first");
        int n = dots.size();
        int from_pos = left_[pos_[from_id]];
        int to_pos = right_[pos_[to_id]];
        
        vector<int> result;
        if (from_pos <= to_pos) {
            result.reserve(to_pos - from_pos + 1);
            for (int i = from_pos; i <= to_pos; i++) {
                result.push_back(ord_[i]);
            }
        } else {
            result.reserve(n - from_pos + to_pos + 1);
            for (int i = from_pos; i < n; i++) {
                result.push_back(ord_[i]);
            }
            for (int i = 0; i <= to_pos; i++) {
                result.push_back(ord_[i]);
            }
        }
        return result;
    }
    
    /**
     * 範囲内の頂点数を返す（vectorを構築せずにカウントのみ）
     * 計算量: O(1)
     */
    int range_count(int from_id, int to_id) const {
        assert(built_ && "Call build() first");
        int n = dots.size();
        int from_pos = left_[pos_[from_id]];
        int to_pos = right_[pos_[to_id]];
        
        if (from_pos <= to_pos) {
            return to_pos - from_pos + 1;
        } else {
            return n - from_pos + to_pos + 1;
        }
    }
    
    // ソートした座標列を返す（非破壊）
    vector<P> sorted() const {
        assert(built_ && "Call build() first");
        vector<P> result(dots.size());
        for (int i = 0; i < (int)dots.size(); i++) {
            result[i] = dots[ord_[i]];
        }
        return result;
    }
};

void test_angular_sort(){
    cout << "=== Angular Sort Test ===" << endl;
    
    // テスト1: デフォルト設定（反時計回り、始線=0°）
    cout << "\n[Test 1] CCW from 0 deg (default):" << endl;
    {
        AngularSort ags;
        ags.add(1, 0);   // 0°
        ags.add(1, 1);   // 45°
        ags.add(0, 1);   // 90°
        ags.add(-1, 1);  // 135°
        ags.add(-1, 0);  // 180°
        ags.add(-1, -1); // 225°
        ags.add(0, -1);  // 270°
        ags.add(1, -1);  // 315°
        
        ags.build();
        auto v = ags.sorted();
        for(auto e:v){
            cout << "(" << e.first << ", " << e.second << ") ";
        }
        cout << endl;
        // 期待: (1,0) → (1,1) → (0,1) → (-1,1) → (-1,0) → (-1,-1) → (0,-1) → (1,-1)
    }
    
    // テスト2: 時計回り、始線=0°
    cout << "\n[Test 2] CW from 0 deg:" << endl;
    {
        AngularSort ags;
        ags.set_clockwise(true);
        ags.add(1, 0);
        ags.add(0, 1);
        ags.add(-1, 0);
        ags.add(0, -1);
        
        ags.build();
        auto v = ags.sorted();
        for(auto e:v){
            cout << "(" << e.first << ", " << e.second << ") ";
        }
        cout << endl;
        // 期待: (1,0) → (0,-1) → (-1,0) → (0,1)
    }
    
    // テスト3: 反時計回り、始線=90°
    cout << "\n[Test 3] CCW from 90 deg:" << endl;
    {
        AngularSort ags;
        ags.set_start_axis_deg(90);
        ags.add(1, 0);
        ags.add(0, 1);
        ags.add(-1, 0);
        ags.add(0, -1);
        
        ags.build();
        auto v = ags.sorted();
        for(auto e:v){
            cout << "(" << e.first << ", " << e.second << ") ";
        }
        cout << endl;
        // 期待: (0,1) → (-1,0) → (0,-1) → (1,0)
    }
    
    // テスト4: 時計回り、始線=90°
    cout << "\n[Test 4] CW from 90 deg:" << endl;
    {
        AngularSort ags;
        ags.set_start_axis_deg(90);
        ags.set_clockwise(true);
        ags.add(1, 0);
        ags.add(0, 1);
        ags.add(-1, 0);
        ags.add(0, -1);
        
        ags.build();
        auto v = ags.sorted();
        for(auto e:v){
            cout << "(" << e.first << ", " << e.second << ") ";
        }
        cout << endl;
        // 期待: (0,1) → (1,0) → (0,-1) → (-1,0)
    }
    
    // テスト5: 中心点を変更
    cout << "\n[Test 5] Center at (2, 2):" << endl;
    {
        AngularSort ags;
        ags.set_center(2, 2);
        ags.add(3, 2);  // 相対: (1, 0) = 0°
        ags.add(2, 3);  // 相対: (0, 1) = 90°
        ags.add(1, 2);  // 相対: (-1, 0) = 180°
        ags.add(2, 1);  // 相対: (0, -1) = 270°
        
        ags.build();
        auto v = ags.sorted();
        for(auto e:v){
            cout << "(" << e.first << ", " << e.second << ") ";
        }
        cout << endl;
        // 期待: (3,2) → (2,3) → (1,2) → (2,1)
    }
    
    // テスト6: get_order
    cout << "\n[Test 6] get_order:" << endl;
    {
        AngularSort ags;
        ags.add(0, -1);  // idx=0, 270°
        ags.add(1, 0);   // idx=1, 0°
        ags.add(-1, 0);  // idx=2, 180°
        ags.add(0, 1);   // idx=3, 90°
        
        ags.build();
        auto ids = ags.get_order();
        for(auto id:ids){
            cout << id << " ";
        }
        cout << endl;
        // 期待: [1, 3, 2, 0] (0° → 90° → 180° → 270°)
    }
    
    // テスト7: 任意の始線（45°方向）
    cout << "\n[Test 7] Custom start axis (1, 1) = 45 deg:" << endl;
    {
        AngularSort ags;
        ags.set_start_axis(1, 1);
        ags.add(1, 0);
        ags.add(0, 1);
        ags.add(-1, 0);
        ags.add(0, -1);
        ags.add(1, 1);  // 始線上
        
        ags.build();
        auto v = ags.sorted();
        for(auto e:v){
            cout << "(" << e.first << ", " << e.second << ") ";
        }
        cout << endl;
        // 期待: (1,1) → (0,1) → (-1,0) → (0,-1) → (1,0)
    }
    
    // テスト8: 同一偏角で距離が異なる点（近い順）
    cout << "\n[Test 8] Same angle, near first (default):" << endl;
    {
        AngularSort ags;
        ags.add(1, 0);   // 距離 1
        ags.add(2, 0);   // 距離 2
        ags.add(3, 0);   // 距離 3
        ags.add(1, 1);   // 45°, 距離 √2
        ags.add(2, 2);   // 45°, 距離 2√2
        
        ags.build();
        auto v = ags.sorted();
        for(auto e:v){
            cout << "(" << e.first << ", " << e.second << ") ";
        }
        cout << endl;
        // 期待: 0°方向は (1,0)→(2,0)→(3,0), 45°方向は (1,1)→(2,2)
    }
    
    // テスト9: 同一偏角で距離が異なる点（遠い順）
    cout << "\n[Test 9] Same angle, far first:" << endl;
    {
        AngularSort ags;
        ags.set_near_first(false);
        ags.add(1, 0);   // 距離 1
        ags.add(2, 0);   // 距離 2
        ags.add(3, 0);   // 距離 3
        ags.add(1, 1);   // 45°, 距離 √2
        ags.add(2, 2);   // 45°, 距離 2√2
        
        ags.build();
        auto v = ags.sorted();
        for(auto e:v){
            cout << "(" << e.first << ", " << e.second << ") ";
        }
        cout << endl;
        // 期待: 0°方向は (3,0)→(2,0)→(1,0), 45°方向は (2,2)→(1,1)
    }
    
    // テスト10: 複合テスト（始線90°、時計回り、遠い順）
    cout << "\n[Test 10] Combined: start=90deg, CW, far first:" << endl;
    {
        AngularSort ags;
        ags.set_start_axis_deg(90);
        ags.set_clockwise(true);
        ags.set_near_first(false);
        ags.add(0, 1);   // 90°, 距離 1
        ags.add(0, 2);   // 90°, 距離 2
        ags.add(1, 0);   // 0°
        ags.add(-1, 0);  // 180°
        
        ags.build();
        auto v = ags.sorted();
        for(auto e:v){
            cout << "(" << e.first << ", " << e.second << ") ";
        }
        cout << endl;
        // 時計回りで90°から: (0,2)→(0,1)→(1,0)→(-1,0)
    }
    
    // テスト11: range関数（基本）
    cout << "\n[Test 11] range function (basic):" << endl;
    {
        AngularSort ags;
        ags.add(1, 0);   // idx=0, 0°
        ags.add(0, 1);   // idx=1, 90°
        ags.add(-1, 0);  // idx=2, 180°
        ags.add(0, -1);  // idx=3, 270°
        
        ags.build();
        // ソート順: 0→1→2→3 (0°→90°→180°→270°)
        auto r1 = ags.range(0, 2);  // 0°から180°まで
        cout << "0 to 2: ";
        for(auto e:r1){
            cout << e << " ";
        }
        cout << endl;
        // 期待: [0, 1, 2]
        
        auto r2 = ags.range(2, 0);  // 180°から0°まで（円周を跨ぐ）
        cout << "2 to 0: ";
        for(auto e:r2){
            cout << e << " ";
        }
        cout << endl;
        // 期待: [2, 3, 0]
    }
    
    // テスト12: range関数（同一偏角のグループ）
    cout << "\n[Test 12] range function (same angle group):" << endl;
    {
        AngularSort ags;
        ags.add(1, 0);   // idx=0, 0°
        ags.add(2, 0);   // idx=1, 0°
        ags.add(3, 0);   // idx=2, 0°
        ags.add(0, 1);   // idx=3, 90°
        ags.add(0, 2);   // idx=4, 90°
        ags.add(-1, 0);  // idx=5, 180°
        
        ags.build();
        // ソート順: 0,1,2(0°) → 3,4(90°) → 5(180°)
        auto r1 = ags.range(1, 3);  // idx1(0°)からidx3(90°)まで
        cout << "1 to 3: ";
        for(auto e:r1){
            cout << e << " ";
        }
        cout << endl;
        // 期待: [0, 1, 2, 3, 4] (0°グループ全体 + 90°グループ全体)
        
        auto r2 = ags.range(0, 4);  // idx0(0°)からidx4(90°)まで
        cout << "0 to 4: ";
        for(auto e:r2){
            cout << e << " ";
        }
        cout << endl;
        // 期待: [0, 1, 2, 3, 4]
    }
    
    // テスト13: 設定を変えて再build
    cout << "\n[Test 13] rebuild with different settings:" << endl;
    {
        AngularSort ags;
        ags.add(1, 0);   // idx=0, 0°
        ags.add(0, 1);   // idx=1, 90°
        ags.add(-1, 0);  // idx=2, 180°
        ags.add(0, -1);  // idx=3, 270°
        
        // 反時計回りでbuild
        ags.build();
        auto r1 = ags.range(0, 2);
        cout << "CCW 0 to 2: ";
        for(auto e:r1){
            cout << e << " ";
        }
        cout << endl;
        // 期待: [0, 1, 2]
        
        // 時計回りに変更してrebuild
        ags.set_clockwise(true);
        ags.build();
        auto r2 = ags.range(0, 2);
        cout << "CW 0 to 2: ";
        for(auto e:r2){
            cout << e << " ";
        }
        cout << endl;
        // 期待: [0, 3, 2] (0° → 270° → 180°)
    }
    
    // テスト14: range_count
    cout << "\n[Test 14] range_count:" << endl;
    {
        AngularSort ags;
        ags.add(1, 0);   // idx=0
        ags.add(0, 1);   // idx=1
        ags.add(-1, 0);  // idx=2
        ags.add(0, -1);  // idx=3
        
        ags.build();
        cout << "count(0,2) = " << ags.range_count(0, 2) << endl;  // 期待: 3
        cout << "count(2,0) = " << ags.range_count(2, 0) << endl;  // 期待: 3
    }

    cout << "\n=== All tests completed ===" << endl;
}

void test_ABC442(){
    using ll = long long;
    ll n,q; cin >> n >> q;
    AngularSort ags;
    for(int i=0; i<n; i++){
        ll x,y; cin >> x >> y;
        ags.add(x,y);
    }
    ags.set_start_axis_deg(90);
    ags.set_clockwise(true);
    ags.set_near_first(true);
    ags.build();
    
    for(int i=0; i<q; i++){
        int a,b; cin >> a >> b; a--,b--;
        auto ans = ags.range_count(a,b);
        cout << ans << endl;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // test_angular_sort();
    test_ABC442();
}