/**
*    author:  shu8Cream
*    created: 2024/06/01 14:41:21
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T=ll>
struct BfsGrid {
    static constexpr int dx[4] = {1,0,-1,0};
    static constexpr int dy[4] = {0,1,0,-1};
    int h,w;
    vector<string> board;
    vector<vector<T>> dist;
    vector<vector<pair<int,int>>> prev;
    BfsGrid(vector<string> grid):board(grid){
        h = grid.size();
        w = grid[0].size();
        dist.resize(h,vector<T>(w,-1));
        prev.resize(h,vector<pair<int,int>>(w,make_pair(-1,-1)));
    }

    bool out_of_grid(int x, int y, bool wall=true){
        if(x<0 || x>=h || y<0 || y>=w) return true;
        return (wall ? board[x][y]=='#' : false);
    }
    vector<vector<T>> get_dist(int sx, int sy){
        dist[sx][sy]=0;
        queue<pair<int,int>> q;
        q.emplace(sx,sy);
        while(!q.empty()){
            auto[i,j] = q.front(); q.pop();
            for(int v=0;v<4;v++){
                int ni=i+dx[v];
                int nj=j+dy[v];
                if(out_of_grid(ni,nj)) continue;
                if(dist[ni][nj]!=-1) continue;
                dist[ni][nj] = dist[i][j] + 1;
                prev[ni][nj] = make_pair(i,j);
                q.emplace(ni,nj);
            }
        }
        return dist;
    }
    bool isreachable(int sx, int sy, int tx, int ty){
        vector<vector<T>> d = get_dist(sx,sy);
        return d[tx][ty]!=-1;
    }
    vector<pair<int,int>> restore(int tx, int ty){
        vector<pair<int,int>> path;
        while(tx!=-1&&ty!=-1){
            path.emplace_back(tx,ty);
            tie(tx,ty) = prev[tx][ty];
        }
        reverse(path.begin(),path.end());
        return path;
    }
};

void ABC088(){
    int h,w; cin >> h >> w;
    vector<string> s(h);
    for(int i=0;i<h;i++) cin >> s[i];
    BfsGrid bfs(s);
    if(!bfs.isreachable(0,0,h-1,w-1)){
        cout << -1 << endl;
        return;
    }
    vector<vector<ll>> d = bfs.get_dist(0,0);
    int ans = h*w;
    for(int i=0;i<h;i++)for(int j=0;j<w;j++) ans-=s[i][j]=='#';
    vector<pair<int,int>> path = bfs.restore(h-1,w-1);
    ans -= path.size();
    cout << ans << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    ABC088();
}