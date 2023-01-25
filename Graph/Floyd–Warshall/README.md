# ワーシャルフロイド法 / Floyd–Warshall algorithm
## 概要
全点対間最短経路を求めるためのアルゴリズム。 $cost[i][j]$ を頂点 $i$ から頂点 $j$ への最短距離とする。 $i=j$ は閉路を表すため $0$ で初期化する。<br/>
遷移を見るとシンプルなDPと捉えることができる。<br/>
計算量は $O(V^3)$　。

## 実装
- [ワーシャルフロイド法](https://github.com/shu8Cream/algorithm/blob/main/Graph/Floyd–Warshall/warshall_floyd.cpp)

## verify
- [Shortest Path Queries 2 (ABC208D)](https://atcoder.jp/contests/abc208/tasks/abc208_d)
