# Dynamic Connectivity
## 概要
### Offline
Q個のクエリを時系列だと考える。各辺の追加・削除を「uとvを結ぶ辺は時刻lから時刻rまで存在した」という情報に変換することができる。
この情報を長さQのセグ木（完全二分木）に乗せることを考える。区間[l,r)に対応する $ O(\log{Q}) $ 個のノードに辺の情報(u,v)を乗せる。
この木上をDFSする。ノードに到達・帰還したときにそのノードに存在する情報を処理する。到達したときに辺の追加を行い、帰還したとき辺の削除を行う。辺の追加はUnionFindを用いることで連結性の管理ができるが、辺の削除が問題になる。実はこのDFSを行うと辺の削除は必ず最新の辺の追加に対する削除しか行われない。最新追加辺の削除はUndo可能UnionFindを用いることで管理できる。

### 例
| time | type   | U | V |
| ---- | ------ | - | - |
| 1    | link   | 1 | 2 |
| 2    | link   | 2 | 3 |
| 3    | query  | 1 | 3 |
| 4    | cut    | 1 | 2 |
| 5    | query  | 1 | 2 |
| 6    | link   | 1 | 3 |
| 7    | query  | 1 | 2 |

(u,v,l,r) = (1,2,1,5), (2,3,2,8), (1,3,6,9)

```shell=
                                  +-----+
                                  |     |
                                  +-----+
                  +-----+                         +-----+
                  |(1,2)|                         |(2,3)|
                  +-----+                         +-----+
          +-----+         +-----+         +-----+         +-----+
          |     |         |(2,3)|         |     |         |(1,3)|
          +-----+         +-----+         +-----+         +-----+
      +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+
      |     | |(2,3)| |     | |     | |     | |(1,3)| |     | |     |
      +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+
time:    1       2       3       4       5       6       7       8
```

## 実装
- [Offline Dynamic Connectivity](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/DynamicConnectivity/offline_dynamic_connectivity.cpp)


## verify
- [Dynamic connectivity contest A. Connect and Disconnect](https://codeforces.com/gym/100551/submission/257005157)
- [Problem D: Graph Construction (AOJ)](https://onlinejudge.u-aizu.ac.jp/solutions/problem/2235/review/9108953/shu8Cream/C++17)

## 参考
- [Decomposable searching problem - オフラインの場合](https://yukicoder.me/wiki/offline_dsp)
- [解説:#16 Dynamic connectivity (Fuwa Online Judge)](https://oj.fuwa.dev/problems/16/editorial)
- [Offline-Dynamic-Connectivity (Luzhiled's memo)](https://ei1333.github.io/luzhiled/snippets/other/offline-dynamic-connectivity.html)
