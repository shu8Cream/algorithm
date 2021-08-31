# アルゴリズムのMyライブラリ
主に競技プログラミングで使用する、自分用のライブラリです。
C++17で実装していますが、一部C++14想定のものも含まれます。
徐々に増え次第分類し整理していきます。

## 整数
整数に関するアルゴリズム

### mod
- [mod_power](https://github.com/shu8Cream/algorithm/blob/main/mod_power.cpp)
- [二項係数(mod)](https://github.com/shu8Cream/algorithm/blob/main/nCk.cpp)

### 約数
- [約数列挙](https://github.com/shu8Cream/algorithm/blob/main/divisor.cpp)
- [最大公約数(ユークリッドの互除法)](https://github.com/shu8Cream/algorithm/blob/main/gcd.cpp)
- [最小公倍数](https://github.com/shu8Cream/algorithm/blob/main/lcm.cpp)
- [拡張ユークリッドの互除法](https://github.com/shu8Cream/algorithm/blob/main/ext_gcd.cpp)

### 素数
- [エラトステネスの篩-素因数分解](https://github.com/shu8Cream/algorithm/blob/main/eratosthenes.cpp)


## 探索法
様々な探索手法に関する実装

- [二分探索](https://github.com/shu8Cream/algorithm/blob/main/binary_search.cpp)
- 三分探索


## Graph
グラフに関するアルゴリズム

### DFS・BFS
- [DFS(time stamp)](https://github.com/shu8Cream/algorithm/blob/main/dfs.cpp)
- DFS(グリッド)
- [BFS(template)](https://github.com/shu8Cream/algorithm/blob/main/bfs.cpp)
- BFS(グリッド)
- [トポロジカルソート（BFS実装・閉路検出可能）](https://github.com/shu8Cream/algorithm/blob/main/topological_sort.cpp)

### 最短経路
- [単一始点最短路（Dijkstra法、正辺のみ）](https://github.com/shu8Cream/algorithm/blob/main/dijkstra.cpp)

### 木の関連
- [木の直径](https://github.com/shu8Cream/algorithm/blob/main/tree_diameter.cpp)
- 木の重心
- [LCA(by doubling)](https://github.com/shu8Cream/algorithm/blob/main/lca.cpp)

### 重みつき辺
- [最小全域木（クラスカル法）](https://github.com/shu8Cream/algorithm/blob/main/kruskal.cpp)
- [最小全域木（プリム法）](https://github.com/shu8Cream/algorithm/blob/main/prim.cpp)

## データ構造
様々なデータ構造に関する実装

- [Union-Find(マージテク)](https://github.com/shu8Cream/algorithm/blob/main/unionfind.cpp)
- [Binary Indexed Tree(BIT)](https://github.com/shu8Cream/algorithm/blob/main/BIT.cpp)
- [SegmentTree](https://github.com/shu8Cream/algorithm/blob/main/segment_tree.cpp)

## DP
動的計画法に関する実装

- LIS 

## String
- [Z-algorithm](https://github.com/shu8Cream/algorithm/blob/main/z-algorithm.cpp)


## Others
- [座標圧縮（１次元）](https://github.com/shu8Cream/algorithm/blob/main/compress1.cpp)
- [行列基本演算](https://github.com/shu8Cream/algorithm/blob/main/matrix.cpp)