#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
using ll = long long;
using P = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using Graph = vvi;

Graph to;
vi d;
vi f;

// 深さ優先探索
vector<bool> seen;
void dfs(const Graph &to, int v, int& ptr) {
  d[v] = ptr++; //行きがけ順
  seen[v] = true; // v を訪問済にする
  // v から行ける各頂点 next_v について
  for (auto next_v : to[v]) { 
    if (seen[next_v]) continue; // next_v が探索済だったらスルー
    dfs(to, next_v, ptr); // 再帰的に探索
  }
  f[v] = ptr++; //帰りがけ順
}

int main(){
  int n;
  cin >> n;
  Graph to(n);
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