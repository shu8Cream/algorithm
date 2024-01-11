/**
*    author:  shu8Cream
*    created: 2024/01/11 23:12:55
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll euler(const ll n){
    vector<ll> div;
    ll tn = n;
    for(ll p=2; p*p<=tn; p++){
        if(tn%p==0){
            div.push_back(p);
            while(tn%p==0) tn/=p;
        }
    }
    if(tn!=1) div.push_back(tn);

    int k = div.size();
    int res = 0;
    for(int b=1; b<(1<<k); b++){
        int bcnt = __builtin_popcount(b);
        ll mul = 1;
        for(int i=0; i<k; i++){
            if(b>>i&1) mul *= div[i];
        }
        if(bcnt%2) res += n/mul;
        else res -= n/mul;
    }
    res = n-res;
    return res;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ll n; cin >> n;
    
    ll ans = euler(n);
    cout << ans << endl;
}