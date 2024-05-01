/**
*    author:  shu8Cream
*    created: 2024/04/09 20:51:55
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct UndoableUnionFind{
    int n;
    vector<int> par;
    vector<pair<int,int>> history;
    int group_cnt;
    UndoableUnionFind(){}
    UndoableUnionFind(int n=0): n(n), par(n, -1), group_cnt(n) {}
    int find(int x){
        if(par[x] < 0) return x;
        return find(par[x]);
    }
    bool merge(int x, int y){
        x = find(x); y = find(y);
        history.emplace_back(x,par[x]);
        history.emplace_back(y,par[y]);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x,y); //マージテク
        par[x] += par[y];
        par[y] = x;
        group_cnt--;
        return true;
    }
    bool same(int x, int y) {return find(x) == find(y);}
    int size(int x) {return -par[find(x)];}

    void undo(){
        int u = history.back().first;
        par[history.back().first] = history.back().second;
        history.pop_back();
        int v = history.back().first;
        par[history.back().first] = history.back().second;
        history.pop_back();
        if(u!=v) group_cnt++;
    }

    void snapshot() {
        while (!history.empty()) history.pop_back();
    }

    void rollback() {
        while (!history.empty()) undo();
    }
};

template<typename Q>
struct OfflineDynamicConnectivity{
    struct Edge_info{
        int from, to, start, end;
        Edge_info(int from, int to, int start, int end):
            from(from),to(to),start(start),end(end)
        {}
    };
    int n,q,size,time;
    vector<Edge_info> infos;
    map<pair<int,int>,int> addtime;
    vector<vector<pair<int,int> > > seg;
    vector<Q> query_types;
    UndoableUnionFind uf;

    OfflineDynamicConnectivity(int n, int q): n(n),q(q),uf(n),time(0),query_types(q){
        for(size=1; size<q; size<<=1);
        seg.resize(size<<1);
    }
    void link(Q type, int u, int v){
        if(u>v) swap(u,v);
        addtime[{u,v}] = time;
        query_types[time++] = type;
    }
    void cut(Q type, int u, int v){
        if(u>v) swap(u,v);
        auto e = make_pair(u,v);
        infos.emplace_back(u,v,addtime[e],time);
        query_types[time++] = type;
        addtime.erase(e);
    }
    void query(Q type){
        query_types[time++] = type;
    }
    template<typename T>
    void dfs(const T &func, int node=1){
        for(auto j : seg[node]) uf.merge(j.first, j.second);
        if(node<size){
            dfs(func, node << 1);
            dfs(func, node << 1 | 1);
        }else{
            func(node-size, uf);
        }
        for(auto j : seg[node]) uf.undo();
    }
    template<typename T>
    void run(const T &func, int node=1){
        for(auto &[e,time]:addtime) infos.emplace_back(e.first,e.second,time,size);
        for(auto i:infos){
            int l = i.start+size;
            int r = i.end+size;
            for(; l<r; l>>=1,r>>=1){
                if(r&1) seg[--r].emplace_back(i.from,i.to);
                if(l&1) seg[l++].emplace_back(i.from,i.to);
            }
        }
        dfs(func,1);
    }
};

void cf100551A(){
    FILE *in, *out;
    in = fopen("connect.in", "r");
    out = fopen("connect.out", "w");
    int n,q;
    fscanf(in, "%d %d", &n,&q);
    OfflineDynamicConnectivity<char> dc(n,q);
    for(int t=0; t<q; t++){
        char c;
        fscanf(in, " %c", &c);
        if(c=='+'){
            int u,v;
            fscanf(in, "%d %d", &u, &v);
            u--,v--;
            dc.link(c,u,v);
        }
        if(c=='-'){
            int u,v;
            fscanf(in, "%d %d", &u, &v);
            u--,v--;
            dc.cut(c,u,v);
        }
        if(c=='?'){
            dc.query(c);
        }
    }

    dc.run([&](int time, UndoableUnionFind &uf){
        if(time<q && dc.query_types[time]=='?'){
            fprintf(out, "%d\n", uf.group_cnt);
        }
    });
}

void AOJ2235(){
    int n,q; cin >> n >> q;
    OfflineDynamicConnectivity<int> dc(n,q);
    vector<int> u(q),v(q);
    for(int t=0; t<q; t++){
        int op;
        cin >> op >> u[t] >> v[t];
        if(op==1){
            dc.link(op,u[t],v[t]);
        }else if(op==2){
            dc.cut(op,u[t],v[t]);
        }else{
            dc.query(op);
        }
    }
    dc.run([&](int t, UndoableUnionFind &uf){
        if(t<q && dc.query_types[t]==3){
            cout << (uf.same(u[t],v[t]) ? "YES" : "NO") << endl;
        }
    });
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    cf100551A();
    // AOJ2235();
}