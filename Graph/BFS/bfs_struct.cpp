/**
*    author:  shu8Cream
*    created: 2024/06/01 14:04:17
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T=ll>
struct Bfs {
    int n;
    vector<vector<T> > graph;
    vector<T> dist;
    vector<T> prev;
    Bfs(){}
    Bfs(int n, vector<vector<T>> to): n(n),graph(to),dist(n,-1),prev(n,-1){}
    Bfs(ll n, vector<vector<T>> to): n(n),graph(to),dist(n,-1),prev(n,-1){}

    vector<T> get_dist(int s){
        dist[s] = 0;
        queue<int> q; q.push(s);
        while(!q.empty()){
            int v = q.front(); q.pop();
            for(int nv : graph[v]){
                if(dist[nv]!=-1) continue;
                dist[nv] = dist[v] + 1;
                prev[nv] = v;
                q.push(nv);
            }
        }
        return dist;
    }

    vector<T> restore(int t){
        vector<T> path;
        while(t!=-1){
            path.push_back(t);
            t = prev[t];
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ll n; cin >> n;
    
    ll ans = 0;
    cout << ans << endl;
}