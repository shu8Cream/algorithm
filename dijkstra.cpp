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

const ll INF = 8e18;
const int MAX_V = 100100;

struct edge { int to; ll cost; };

ll d[MAX_V];
vector<edge> G[MAX_V];

//始点を与える
void dijkstra(int s) {
    rep (i,MAX_V) d[i] = INF;
    d[s] = 0;
    priority_queue<P, vector<P>, greater<P>> q;
    q.push(P(0, s));
    while (!q.empty()) {
        P p = q.top();
        q.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (auto e : G[v]) {
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                q.push(P(d[e.to], e.to));
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