//
//  ベルマンフォード法　単一始点最短経路問題
//
/*

    負辺を許容し、最短経路問題を解ける
    負の閉路を検出　O(V＊E)
    verify: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B

*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
#define rrep(i,n) for (int i=(n-1); i>=0; i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) int((x).size())
using ll = long long;
using P = pair<ll,ll>;
using vi = vector<ll>;
using vvi = vector<vi>;

template<class T> inline bool chmax(T& a, T b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) { a = b; return true; }
    return false;
}

const ll INF = 8e18;

struct edge {
    ll from, to, cost;
};

vi dist;
// trueなら負閉路を含む
bool bellman_ford(vector<edge> &egs, int n, int s){
    dist.assign(n,INF);
    dist[s] = 0;
    int cnt = 0;
    while(cnt < n){
        bool end = true;
        for(auto e : egs){
            if(dist[e.from]!=INF && dist[e.from]+e.cost<dist[e.to]){
                dist[e.to] = dist[e.from] + e.cost;
                end = false;
            }
        }
        if(end) break;
        cnt++;
    }
    return (cnt==n);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n,m,r; cin >> n >> m >> r;
    vector<edge> eds(m);
    rep(i,m){
        int s,t,d; cin >> s >> t >> d;
        eds[i].from = s;
        eds[i].to = t;
        eds[i].cost = d;
    }
    if(bellman_ford(eds, n, r)) cout << "NEGATIVE CYCLE" << endl;
    else{
        rep(i,n){
            if(dist[i]==INF) cout << "INF" << endl;
            else cout << dist[i] << endl;
        }
    }
}