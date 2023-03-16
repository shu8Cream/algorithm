# 木の直径 / Tree Diameter
## 概要
最も長い単純（同じ頂点を2度通らない）パス

## アルゴリズム
1. 頂点を1つ選び、頂点を $a$ とする。
2. 頂点 $a$ から最も遠い点を１つ選び、頂点 $b$ とする。
3. 頂点 $b$ から最も遠い点を１つ選び、頂点 $c$ とする。
4.  $b$ と $c$ を結ぶパスが直径である。

## 実装
- [木の直径＆頂点列挙(重みなし辺 BFS ver)](https://github.com/shu8Cream/algorithm/blob/main/Graph/TreeDiameter/tree_diameter_bfs.cpp)
- [木の直径(重みなし辺 DFS ver)](https://github.com/shu8Cream/algorithm/blob/main/Graph/TreeDiameter/tree_diameter_dfs.cpp)
- [木の直径＆頂点列挙(重み付き辺 BFS ver)](https://github.com/shu8Cream/algorithm/blob/main/Graph/TreeDiameter/tree_diameter_wbfs.cpp)
- [木の直径(重み付き辺 DFS ver)](https://github.com/shu8Cream/algorithm/blob/main/Graph/TreeDiameter/tree_diameter_wdfs.cpp)

## verify
- [GRL_5_A Diameter of a Tree](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_A)
- [木の直径（2）](https://algo-method.com/tasks/976)
