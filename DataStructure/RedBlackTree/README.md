# 赤黒木
## 概要
説明を書く


## Policy Based Data Structures

### k番目に小さい値が取得できるSet
```cpp
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

int main(){
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> rbt;
    rbt.insert(1);
    rbt.insert(3);
    rbt.insert(9);
    rbt.insert(27);
    rbt.insert(81);

    // k番目の値を取得
    // log(n)
    cout << *rbt.find_by_order(0) << endl; // 1
    cout << *rbt.find_by_order(1) << endl; // 3
    cout << *rbt.find_by_order(2) << endl; // 9
    cout << (rbt.end()==*rbt.find_by_order(10)) << endl; // true

    // kが何番目か、lower_bound
    // log(n)
    cout << rbt.order_of_key(-1) << endl; // 0
    cout << rbt.order_of_key(1) << endl; // 0
    cout << rbt.order_of_key(3) << endl; // 1
    cout << rbt.order_of_key(5) << endl; // 2
    cout << rbt.order_of_key(100) << endl; // 5
}
```