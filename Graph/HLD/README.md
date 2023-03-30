# HL分解 / Heavy Light Decomposition
## 概要
木をHeavyな辺とLightな辺に分解することで、木のを更新しながらクエリを処理することができるようになる手法。
前計算として、部分木のサイズや行きがけ順に頂点IDを振り直すため、多くの木に対する処理をこなすことができる。

## 実装
- [HL分解](https://github.com/shu8Cream/algorithm/blob/main/Graph/HLD/heavy_light_decomposition.cpp)

## verify
### LCA
- [Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca)

### 頂点に対するクエリ
- [Vertex Add Path Sum](https://judge.yosupo.jp/problem/vertex_add_path_sum)

### 辺に対するクエリ
- [ABC294G Distance Queries on a Tree](https://atcoder.jp/contests/abc294/tasks/abc294_g)

### Level Ancestor & Jump
- [パ研合宿2022day1G Ancestor Query](https://atcoder.jp/contests/pakencamp-2022-day1/tasks/pakencamp_2022_day1_g)

## 参考
