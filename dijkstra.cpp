//  
//  Dijkstra(ダイクストラ法、正辺のみ)
//
/*

    単一視点最短路問題
    計算量：ヒープなしO(V^2）、ヒープありO(ElogV)

*/
#include <bits/stdc++.h>
using namespace std;
#define  rep(i,n) for (int i=0; i<(n); i++)
using ll = long long;
using P = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vi>;
using Graph = vvi;

const int INF = 1e9+1;
const int MAX_V = 100100;

struct edge { int to, cost; };

int V, d[MAX_V]; //dはコスト配列
vector<edge> G[MAX_V]; //辺とコストを受け取るグラフ

void dijkstra(int s) { //始点を与える
    rep (i,MAX_V) d[i] = INF;
    d[s] = 0;
    // 小さい順に取り出される優先度付きキュー
    priority_queue<P, vector<P>, greater<P>> que;
    que.push(P(0, s));
    while (!que.empty()) {
        P p = que.top();
        que.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (auto e : G[v]) {
        if (d[e.to] > d[v] + e.cost) {
            d[e.to] = d[v] + e.cost;
            que.push(P(d[e.to], e.to));
        }
        }
    }
}

int main(){
    int v,e,r;
    cin >> v >> e >> r;
    rep(i,e){
        int s,t,d;
        cin >> s >> t >> d;
        G[s].push_back((edge){t,d});
    }
    dijkstra(r);
    rep(i,v){
        if(d[i]==INF) cout << "INF" << endl;
        else cout << d[i] << endl;
    }
}