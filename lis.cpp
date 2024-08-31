/**
*    author:  shu8Cream
*    created: 2024/09/01 02:10:26
**/

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct LIS {
    const T inf = numeric_limits<T>::max();
    int n;
    vector<T> A;
    vector<T> id; // Aのどこに挿入したかの情報
    vector<T> a;
    int lis_size;
    LIS(){}
    // strict: T/F -> 狭義/広義
    LIS(vector<T> a, bool strict=true): n(int(a.size())), a(a), A(n,inf),id(n){
        for(int i=0; i<n; i++){
            if(strict) id[i] = distance(A.begin(), lower_bound(A.begin(), A.end(), a[i]));
            else id[i] = distance(A.begin(), upper_bound(A.begin(), A.end(), a[i]));
            A[id[i]] = a[i];
        }
        lis_size = *max_element(id.begin(), id.end())+1;
    }

    int size(){ return lis_size; }

    vector<int> restore_id(){
        vector<int> res(lis_size);
        int m = lis_size-1; // 後ろから
        for(int i=n-1; i>=0; i--)if(id[i]==m) res[m--] = i;
        return res;
    }

    vector<T> restore_val(){
        vector<T> res(lis_size);
        int m = lis_size-1;
        for(int i=n-1; i>=0; i--)if(id[i]==m) res[m--] = a[i];
        return res;
    }
};

void ABC134E(){
    long n; cin >> n;
    vector<long> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    vector<long> ra = a;
    reverse(ra.begin(),ra.end());
    LIS<long> lis(ra,false);
    cout << lis.size() << endl;
}

void ABC369F(){
    long h,w,n; cin >> h >> w >> n;
    vector<long> r(n),c(n);
    for(int i=0;i<n;i++) cin >> r[i] >> c[i];
    vector<pair<long,long>> rc(n);
    for(int i=0;i<n;i++) rc[i] = {r[i],c[i]};
    sort(rc.begin(),rc.end());

    vector<long> cc(n);
    for(int i=0;i<n;i++) cc[i] = rc[i].second;
    LIS<long> lis(cc,false);
    cout << lis.size() << endl;
    int x = 1, y = 1;
    for(auto id:lis.restore_id()){
        if(x!=rc[id].first) cout << string(abs(x-rc[id].first),'D');
        if(y!=rc[id].second) cout << string(abs(y-rc[id].second),'R');
        x = rc[id].first;
        y = rc[id].second;
    }
    if(x-h) cout << string(abs(x-h),'D');
    if(y-w) cout << string(abs(y-w),'R');
    cout << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    // ABC134E();
    ABC369F();
}