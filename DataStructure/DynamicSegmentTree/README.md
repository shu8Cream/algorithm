# Dynamic Segment Tree
## 概要
必要なところだけ作るセグメントツリー。座標圧縮の必要がなくなるので便利。

## 計算量
普通のセグ木の場合、要素へのアクセスは $O(1)$ だが、このデータ構造では $O(\log N)$ かかる。

## 実装
- [DynamicSegmentTree（抽象化）](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/DynamicSegmentTree/dynamic_segment_tree.cpp)
- [DynamicSegmentTree（RSQ）](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/DynamicSegmentTree/dynamic_segtree_for_rangesum.cpp)
- [RangeCountQuery](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/DynamicSegmentTree/range_count_query.cpp)
<!-- - [RangeSetCount&SumQuery](https://github.com/shu8Cream/algorithm/blob/main/DataStructure/DynamicSegmentTree/range_set_count_sum_query.cpp) -->

## Verified

## 参考
- [Dynamic Segment Tree の ACL 風実装](https://lorent-kyopro.hatenablog.com/entry/2021/03/12/025644)
- [Dynamic Segment Tree - scrapbox](https://scrapbox.io/data-structures/Dynamic_Segment_Tree)
- [Range Sum Query (動的セグメント木)](https://tjkendev.github.io/procon-library/cpp/range_query/dynamic_segment_tree.html)
