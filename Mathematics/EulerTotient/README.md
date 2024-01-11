# オイラーのφ関数 / Euler's Totient Function
## 概要
読み方はオイラーのトーシェント関数。オイラーのファイ関数やオイラーの関数とも呼ばれる。正の整数$n$に対して、$n$と互いに素である$1$以上$n$以下の自然数の個数を$φ(n)$と表す。
$1$以上$n$以下の自然数の中で、$n$の素因数$p_i$を素因数に持つ自然数の集合を$S_i$とした時、包除原理を用いることで$|\bigcup_{i=1}^{k}S_i|$を求めることができる（$k$は$n$の素因数の個数）。この余事象が$φ(n)$である。

## 実装
- [オイラーのφ関数](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/EulerTotient/eulers_totient.cpp)

## verify
- [オイラーのφ関数(AOJ)](https://onlinejudge.u-aizu.ac.jp/solutions/problem/NTL_1_D/review/8754943/shu8Cream/C++17)

## 参考
