# Manhattan Minimum Spanning Tree
## 概要
二次元平面上にN個の点が与えられる。2点間の距離をマンハッタン距離で定義した場合のMSTを求める。<br/>
$O(N \log N)$で$O(N)$本の候補辺を列挙する。

## アルゴリズム
8領域に分割し、各領域を等距離線で平面走査することで不要な辺を削除することで必要辺を列挙する。

## 実装
- [Manhattan MST](https://github.com/shu8Cream/algorithm/blob/main/Graph/ManhattanMST/manhattan_mst.cpp)

## verify
- [Manhattan MST(yosupo judge)](https://judge.yosupo.jp/problem/manhattanmst)
- [ABC283F Permutation Distance](https://atcoder.jp/contests/abc283/tasks/abc283_f)
- [ABC065D Built?](https://atcoder.jp/contests/abc065/tasks/arc076_b)

## 参考
- H. Zhou, N. Shenoy, W. Nicholls, "Efficient minimum spanning tree construction without Delaunay triangulation," Information Processing Letters, vol. 81, no. 5, pp. 271-276, 2002.
