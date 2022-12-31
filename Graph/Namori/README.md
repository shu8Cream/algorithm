# なもりグラフ / 英名を書きたい
## 概要
木に一辺追加したサイクルがひとつあるグラフ。N頂点N辺。

## 判定
連結なグラフがなもりグラフであるか（もしくはなもりの森であるか）を判定。
```cpp
// n: 頂点数
UnionFind uf(n);
rep(i,n) uf.merge(a[i],b[i]);
vi cnt(n);
rep(i,n)cnt[uf.find(a[i])]++; // 貼った辺の片側の頂点を見る
rep(i,n)if(uf.find(i)==i){
    if(uf.sz(i)!=cnt[i]){
        return false;
    }
}
return true;
```

## 実装
- [なもりグラフ](https://github.com/shu8Cream/algorithm/blob/main/Graph/Namori/namori.cpp)
