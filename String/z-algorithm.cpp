//
//  Z-アルゴリズム
//
/*

    入力文字列Sとして
    SとS[i...]の共通接頭辞の長さの配列を返す
    通常ならO(N^2)かかるところをZならO(N)でできる

*/
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
using vi = vector<int>;

vi Zalgo(string str){
    int n = str.size();
    vi a(n,0);
    int from = -1, last = -1;
    for(int i=1; i<n; i++){
        int &same=a[i];
        if(from != -1){
            same = min(a[i-from], last - i);
            same = max(0, same);
        }
        while(i + same < n && str[same]==str[i+same]) same++;
        if(last < i+same){
            last = i + same;
            from = i;
        }
    }
    a[0]=n;
    return a;
}

int main() {
    string str;
    cin >> str;
    auto a = Zalgo(str);
    for(auto elem : a) cout << elem << " "; cout << endl;
}