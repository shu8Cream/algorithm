# トポロジカルソート / Topological Sort
## 概要
DAGに対して、辺の向きを揃えるソートアルゴリズム。
入次数を数えながら、DFS/BFSをすることでソートを行う。
閉路がある場合ソートできないが、BFSの実装ではこの性質を使うことで閉路検出できる。

## 実装
- [トポロジカルソート](https://github.com/shu8Cream/algorithm/blob/main/Graph/TopSort/topological_sort.cpp)

## verify
- [ABC216D Pair of Balls](https://atcoder.jp/contests/abc216/submissions/25490365)
- [ABC223D Restricted Permutation](https://atcoder.jp/contests/abc223/tasks/abc223_d)
- [ABC291E Find Permutation](https://atcoder.jp/contests/abc291/tasks/abc291_e)
