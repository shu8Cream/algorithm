//
//　Grand Common Divisor
//
/*

    ユークリッドの互除法での実装

*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
using ll = long long;

ll gcd(ll a, ll b){
    if(a<0) a = -a;
    if(b<0) b = -b;
    if(b == 0) return a;
    else return gcd(b, a % b);
}

int main(){
    int n,m;
    cin >> n >> m;
    int k = gcd(n, m);
    cout << k << endl;
}