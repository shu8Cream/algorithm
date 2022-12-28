# アルゴリズムのMyライブラリ
主に競技プログラミングで使用する、自分用のライブラリです。
C++17で実装していますが、一部C++14想定のものも含まれます。
徐々に増え次第分類し整理していきます。

## 整数
整数に関するアルゴリズム

### mod
- [mod_int](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/mod_int.cpp)
- [mod_power](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/mod_power.cpp)
- [二項係数(mod)](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/nCk.cpp)

### 約数
- [約数列挙](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/divisor.cpp)
- [最大公約数（ユークリッドの互除法）](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/gcd.cpp)
- [最小公倍数](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/lcm.cpp)
- [拡張ユークリッドの互除法](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/ext_gcd.cpp)

### 素数
- [エラトステネスの篩-素因数分解](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/eratosthenes.cpp)
- [ミラーラビン素数判定法](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/miller_rabin.cpp)

## Graph
グラフに関するアルゴリズム

### general
- [DFS(time stamp)](https://github.com/shu8Cream/algorithm/blob/main/Graph/dfs.cpp)
- DFS(グリッド)
- [BFS(template)](https://github.com/shu8Cream/algorithm/blob/main/Graph/bfs.cpp)
- BFS(グリッド)
- [トポロジカルソート（BFS実装・閉路検出可能）](https://github.com/shu8Cream/algorithm/blob/main/Graph/topological_sort.cpp)
- [強連結成分分解（SCC）](https://github.com/shu8Cream/algorithm/blob/main/Graph/scc.cpp)
- [なもりグラフ](https://github.com/shu8Cream/algorithm/blob/main/Graph/namori.cpp)

### 最短経路
- [単一始点最短路（ダイクストラ法（最短経路木）正辺のみ）](https://github.com/shu8Cream/algorithm/blob/main/Graph/dijkstra.cpp)
- [ベルマンフォード法（負辺可、負の閉路検出、O(V＊E)）](https://github.com/shu8Cream/algorithm/blob/main/Graph/bellmanford.cpp)

### 木の関連
- [木の直径](https://github.com/shu8Cream/algorithm/blob/main/Graph/tree_diameter.cpp)
- 木の重心
- [LCA(by doubling)](https://github.com/shu8Cream/algorithm/blob/main/Graph/lca.cpp)
- [LCA(EulerTour & RmQ)](https://github.com/shu8Cream/algorithm/blob/main/Graph/LCA_euler_tour.cpp)

### 重みつき辺
- [最小全域木（クラスカル法）](https://github.com/shu8Cream/algorithm/blob/main/Graph/kruskal.cpp)
- [最小全域木（プリム法）](https://github.com/shu8Cream/algorithm/blob/main/Graph/prim.cpp)

### ネットワークフロー
- [最大流問題（Ford-Fulkerson）](https://github.com/shu8Cream/algorithm/blob/main/Graph/FordFulkerson.cpp)
- [最大流問題（Dinic）]
- [最小費用流問題]

## Geometry

- [基本要素(未verify)](https://github.com/shu8Cream/algorithm/blob/main/Geometry/base.cpp)
- [偏角ソート](https://github.com/shu8Cream/algorithm/blob/main/Geometry/argument_sort.cpp)

## データ構造
様々なデータ構造に関する実装

- [Union-Find（マージテク）](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/unionfind.cpp)
- [Undo可能なUnion-Find](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/undoable_unionfind.cpp)
- [BinaryIndexedTree(BIT)](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/BIT)
- [SegmentTree](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/segment_tree.cpp)
- [SplayTree](https://github.com/shu8Cream/algorithm/blob/main/splay_tree.cpp)
- [SparseTable](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/sparse_table.cpp)
- [Doubling](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/doubling.cpp)
- [BinaryTrie](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/binary_trie.cpp)
- [永続Stack](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/persistent_stack.cpp)

## DP
動的計画法に関する実装

- [LIS（最長増加部分列）](https://github.com/shu8Cream/algorithm/blob/main/lis.cpp) 
- [LCS（最長共通部分列）](https://github.com/shu8Cream/algorithm/blob/main/LCS.cpp)
- [編集距離（レーベンシュタイン距離）](https://github.com/shu8Cream/algorithm/blob/main/EditDistance.cpp)

## String
文字列に関するアルゴリズム

- [Z-algorithm](https://github.com/shu8Cream/algorithm/blob/main/String/z-algorithm.cpp)
- [Manacher]()
- [KMP]()
- [SA-IS]()
- [ローリングハッシュ]()

### 回文
- [基本（判定・列挙）](https://github.com/shu8Cream/algorithm/blob/main/String/Palindrome/basic.cpp)
- [最大回文長（部分文字列）](https://github.com/shu8Cream/algorithm/blob/main/String/Palindrome/longest_palindrome_substring.cpp)


## Others
- [ランダム生成器（実験用）](https://github.com/shu8Cream/algorithm/blob/main/Others/random_generator.cpp)
- [座標圧縮（１次元）](https://github.com/shu8Cream/algorithm/blob/main/Others/compress1.cpp)
- [行列基本演算](https://github.com/shu8Cream/algorithm/blob/main/Others/matrix.cpp)
- [二次元累積和](https://github.com/shu8Cream/algorithm/blob/main/Others/cumulativeSum2D.cpp)
- [n進法変換（未実装）]()
- [有理数クラス](https://github.com/shu8Cream/algorithm/blob/main/Others/RationalNum.cpp)
- [Mo's Algorithm](https://github.com/shu8Cream/algorithm/blob/main/Others/mo_algorithm.cpp)
- [XorShift](https://github.com/shu8Cream/algorithm/blob/main/Others/xorshift.cpp)
- [ランレングス圧縮](https://github.com/shu8Cream/algorithm/blob/main/Others/run_length_encoding.cpp)
- [bubble sort](https://github.com/shu8Cream/algorithm/blob/main/Others/bubble_sort.cpp)
