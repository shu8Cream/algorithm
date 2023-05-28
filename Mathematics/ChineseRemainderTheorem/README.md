# 中国剰余定理 / Chinese Remainder Theorem
## 概要

$$ x \equiv b_1 \pmod {m_1} $$

$$ x \equiv b_2 \pmod {m_2} $$

$$ \vdots $$

$$ x \equiv b_n \pmod {m_n} $$

を満たす $x$ が $0$ 以上 $M$ 未満からただ一つ存在し、それを見つける。<br/>
ただし、 $M = \mathrm{lcm} ( m_1,m_2,...,m_n ) $

よくある問題設定として、直接 $x$ を問うものや巡回群と絡めるものがある。

## 使い方
N元の場合を考える。
求める値を $x$ として、 $x \equiv b_i \pmod {m_i}$ のように変数を置き、計算する。<br/>
計算結果、 $x \equiv r \pmod M$ の $r, M$ を返す。
ただし、 $M = \mathrm{lcm} ( m_1,m_2,...,m_n )$ <br/>
解がない場合は、 $0, -1$ を返す。

## 実装
- [中国剰余定理](https://github.com/shu8Cream/algorithm/blob/main/Mathematics/ChineseRemainderTheorem/chinese_remainder_theorem.cpp)

## verify
- [yukicoder 0186 中華風 (Easy)](https://yukicoder.me/problems/447)

## 発展
- Garnerのアルゴリズム
