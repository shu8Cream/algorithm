//
//  Ford-Fulkerson Algorithm
//
/*

    計算量O(FE) 最大流をF、辺数をEとする
    verify: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_A

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
const ll INF = 8e18;

template<class T> inline bool chmax(T& a, T b) {
    if (a < b) { a = b; return true; }
    return false;
}
template<class T> inline bool chmin(T& a, T b) {
    if (a > b) { a = b; return true; }
    return false;
}

void debug_out() { cout << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
cout << H << " ";
debug_out(T...);
}

#ifdef _DEBUG
#define debug(...) debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

template<typename flow_t>
struct FordFulkerson {
    struct edge {
        int to;
        flow_t cap;
        int rev;
        bool isrev;
        int idx;
    };

    vector<vector<edge>> graph;
    vector<int> used;
    const flow_t INF;
    int timestamp;

    FordFulkerson(int n) : INF(numeric_limits<flow_t>::max()), timestamp(0) {
        graph.resize(n);
        used.assign(n,-1);
    }

    void add_edge(int from, int to, flow_t cap, int idx = -1){
        graph[from].emplace_back((edge){to,cap,sz(graph[to]),false,idx});
        graph[to].emplace_back((edge){from,0,sz(graph[from])-1,true,idx});
    }

    // graph[to][rev]は逆辺
    flow_t dfs(int idx, const int t, flow_t flow){
        if(idx==t) return flow;
        used[idx] = timestamp;
        for(auto &e: graph[idx]){
            if(e.cap>0 && used[e.to]!=timestamp){
                flow_t d = dfs(e.to, t, min(flow, e.cap));
                if(d>0){
                    e.cap-=d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    flow_t max_flow(int s, int t){
        flow_t flow = 0;
        for(flow_t f; (f = dfs(s,t,INF))>0; timestamp++){
            flow += f;
        }
        return flow;
    }

    void output(){
        rep(i,sz(graph)){
            for(auto &e: graph[i]){
                if(e.isrev) continue;
                auto &rev_e = graph[e.to][e.rev];
                debug(i,"->", e.to, " (flow: ", rev_e.cap, "/", e.cap + rev_e.cap, ")");
            }
        }
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int v,e; cin >> v >> e;
    FordFulkerson<ll> g(v);
    rep(i,e){
        int u,v,c; cin >> u >> v >> c;
        g.add_edge(u,v,c,i);
    }
    g.output();
    cout << g.max_flow(0,v-1) << endl;
    g.output();
}