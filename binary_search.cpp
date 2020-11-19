//
//  二分探索（めぐる式）
//
/*

    利点：汎用性が高い

*/
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
using ll = long long;
using P = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using Graph = vvi;

vi a = {1, 14, 32, 51, 51, 51, 243, 419};

bool isOK(int index, int key){
    if(a[index] >= key) return true;
    else return false;
}

int binary_search(int key){
    int ng = -1;
    int ok = (int)a.size();

    while(abs(ok - ng) > 1){
        int mid = (ok + ng) / 2;
        if(isOK(mid, key)) ok = mid;
        else ng = mid;
    }
    return ok;
}

int main() {
    cout << binary_search(1) << endl;
    cout << binary_search(51) << endl;
    cout << binary_search(52) << endl;
}