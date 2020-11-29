//  
//  mod_power
//
/*

    long longの範囲外に累乗が及ぶときに利用
    これは実装で見落としがちなので注意！！

*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll mod_pow(ll a, ll b, ll n){
    if(b==0) return 1;
    if(b%2==0) return a * mod_pow(a, b-1, n) % n;
    else return mod_pow(a * a % n, b / 2, n) % n;
}

int main(){
    int a, b, n;
    cin >> a >> b >> n;
    cout << mod_pow(a, b, n) << endl;
}