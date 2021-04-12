//
//  DFS（深さ優先探索）基本ver.
//
/*

    タイムスタンプ　行きがけ順＋帰りがけ順
    dfsでグラフを渡す時には、参照渡し（値を渡すとデカすぎてTLEする）

*/
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
using ll = long long;
using P = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

vvi to;
vi d;
vi f;

vector<bool> seen;
void dfs(const vvi &to, int v, int& ptr) {
  d[v] = ptr++; //行きがけ順
  seen[v] = true;
  for (auto nv : to[v]) { 
    if (seen[nv]) continue;
    dfs(to, nv, ptr);
  }
  f[v] = ptr++; //帰りがけ順
}

int main(){
  int n;
  cin >> n;
  vvi to(n);
  rep(i,n){
    int u,k;
    cin >> u >> k;
    u--;
    rep(j,k){
      int v;
      cin >> v;
      v--;
      to[u].push_back(v);
      //to[v].push_back(u);
    }
  }
  seen.assign(n,false);
  d.resize(n);
  f.resize(n);
  int ptr = 1; //タイムスタンプ
  rep(i,n){
    if(!seen[i]) dfs(to,i,ptr);
  }
  rep(i,n) cout << i+1 << " " << d[i] << " " << f[i] << endl;
}