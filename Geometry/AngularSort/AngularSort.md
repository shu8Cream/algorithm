# Angular Sort (偏角ソート) - 競プロ用ライブラリ

2次元平面上の点集合を、指定した中心点からの偏角でソートするライブラリ。  
整数演算のみを使用し、浮動小数点数による誤差を回避。

## 実装
- [偏角ソート](https://github.com/shu8Cream/algorithm/blob/main/Geometory/AngularSort/angular_sort.cpp)

## 基本的な使い方

```cpp
AngularSort ags;

// 1. 点を追加
ags.add(1, 2);
ags.add(3, 4);
ags.add(-1, 1);

// 2. 設定（すべてオプション）
ags.set_center(0, 0);        // 中心点（デフォルト: 原点）
ags.set_start_axis(1, 0);    // 始線ベクトル（デフォルト: 右方向）
ags.set_clockwise(false);    // false=反時計回り（デフォルト）
ags.set_near_first(true);    // 同一偏角で近い順（デフォルト）

// 3. ビルド（必須）
ags.build();

// 4. 結果を取得
auto order = ags.get_order();  // ソート順のインデックス列
auto pts = ags.sorted();       // ソート済み座標列
```

---

## 設定メソッド

### `set_center(cx, cy)`

偏角の中心点を設定。デフォルトは原点 `(0, 0)`。

### `set_start_axis(dx, dy)`

始線（0°の方向）を方向ベクトルで指定。デフォルトは `(1, 0)` = 右方向。

```cpp
ags.set_start_axis(0, 1);   // 上方向を0°に
ags.set_start_axis(-1, 0);  // 左方向を0°に
```

### `set_start_axis_deg(deg)`

始線を角度（度数法）で指定。**0, 90, 180, 270 度のみ対応**。

| 角度 | 方向 | ベクトル |
|------|------|----------|
| 0°   | 右   | (1, 0)   |
| 90°  | 上   | (0, 1)   |
| 180° | 左   | (-1, 0)  |
| 270° | 下   | (0, -1)  |

### `set_clockwise(cw)`

- `true`: 時計回り
- `false`: 反時計回り（デフォルト）

### `set_near_first(nf)`

同一偏角上に複数の点がある場合の距離順。

- `true`: 中心に近い順（デフォルト）
- `false`: 遠い順

---

## 取得メソッド

> ⚠️ すべて `build()` 後に使用可能

### `get_order() -> const vector<int>&`

ソート順のインデックス列を返す。

```cpp
// 例: {2, 0, 1} なら、dots[2], dots[0], dots[1] の順
auto order = ags.get_order();
```

### `sorted() -> vector<pair<ll,ll>>`

ソート済みの座標列を返す。

### `get_pos(i) -> int`

点 `i` のソート順位（0-indexed）を返す。

### `size() -> int`

登録された点の数を返す。

---

## 範囲クエリ

### `range(from_id, to_id) -> vector<int>`

ソート順で `from_id` から `to_id` までの範囲にある点のIDを返す（IDは `add` した順のインデックス）。

- 同一偏角の点は全て含める
- ソート順が循環的に扱われる（from > to なら末尾→先頭と回り込む）

```
例: ソート順が [A, B, C, D, E] で range(C, A) を呼ぶと
    → [C, D, E, A] が返る（Cの偏角からAの偏角まで）
```

### `range_count(from_id, to_id) -> int`

範囲内の点数のみを **O(1)** で返す。

---

## 使用例

### 凸包の辺の角度順走査

```cpp
// 凸包の頂点を追加
AngularSort ags;
for (auto& [x, y] : convex_hull) {
    ags.add(x, y);
}

// 重心を中心に、反時計回りでソート
ll gx = 0, gy = 0;
for (auto& [x, y] : convex_hull) { gx += x; gy += y; }
gx /= n; gy /= n;
ags.set_center(gx, gy);
ags.build();

// 頂点 p から頂点 q の範囲にある頂点を列挙
auto ids = ags.range(p_id, q_id);
```

### 始線を変えて再ソート

```cpp
AngularSort ags;
for (...) ags.add(x, y);

// 右から反時計回り
ags.set_start_axis_deg(0);
ags.build();
auto order1 = ags.get_order();

// 上から時計回り
ags.set_start_axis_deg(90);
ags.set_clockwise(true);
ags.build();
auto order2 = ags.get_order();
```

---

## 計算量

| メソッド | 計算量 |
|----------|--------|
| `add()` | O(1) |
| `build()` | O(N log N) |
| `get_order()` | O(1) |
| `sorted()` | O(N) |
| `get_pos()` | O(1) |
| `range()` | O(K) （K = 結果サイズ） |
| `range_count()` | O(1) |

---

## 内部実装メモ

- 偏角比較は**外積 (cross product)** で行い、浮動小数点数での演算を使用しない
- 点を5つの領域に分類:
  - `0`: 始線上（正方向）
  - `1`: 前半（反時計回りなら上半分）
  - `2`: 始線の逆方向
  - `3`: 後半
  - `4`: 中心点（距離0）
- 同一偏角の距離ソートは `stable_sort` で安定的に行う
- `range()` は同一偏角グループの左端・右端を事前計算して効率化

---

## 注意事項

- 座標値は `long long` で扱われる
- 距離の2乗を計算するため、座標の絶対値が約 $3 \times 10^9$ を超えるとオーバーフローの可能性あり
- 設定を変更したら必ず `build()` を再度呼ぶこと


## 参考
https://ngtkana.hatenablog.com/entry/2021/11/13/202103