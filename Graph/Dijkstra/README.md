# ダイクストラ法 / Dijkstra's algorithm
## 概要
単一始点最短経路問題を解くための最良優先探索によるアルゴリズム。


## アルゴリズム
優先度付きキュー（二分ヒープ）: $O((E+V)\log {V})$ （C++のSTLの優先度付きキューはこっち）<br/>
優先度付きキュー（フィボナッチヒープ）: $O(E+V\log {V})$

## 実装
- [ダイクストラ（基本）](https://github.com/shu8Cream/algorithm/blob/main/Graph/Dijkstra/dijkstra.cpp)
- [ダイクストラ（グリッド上）](https://github.com/shu8Cream/algorithm/blob/main/Graph/Dijkstra/dijkstra_ongrid.cpp)
<!-- - [ダイクストラ（二番目）](https://github.com/shu8Cream/algorithm/blob/main/Graph/Dijkstra/dijkstra_second.cpp) -->

## verify
- [GRL_1_A Single Source Shortest Path](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A)
- [ABC252E Road Reduction](https://atcoder.jp/contests/abc252/tasks/abc252_e)
- [PAST第一回J](https://atcoder.jp/contests/past201912-open/tasks/past201912_j)

## 参考
- [ダイクストラ法のよくあるミスと落し方](https://snuke.hatenablog.com/entry/2021/02/22/102734)
