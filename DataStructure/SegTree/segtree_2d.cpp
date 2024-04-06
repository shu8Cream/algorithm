/**
*    author:  shu8Cream
*    created: 2024/04/06 13:39:53
**/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class S, S(*op)(S,S), S(*e)()>
struct segtree2d {
private:
    int h,w;
    int hsize,wsize;
    vector<S> data;

    unsigned int bit_ceil(unsigned int n){
        unsigned int x = 1;
        while(x < (unsigned int)(n)) x*=2;
        return x;
    }

    int id(int r, int c) const { return r*2*wsize+c; }

public:
    segtree2d(): segtree2d(0,0){}
    segtree2d(int h, int w): h(h),w(w) {
        hsize = (int)bit_ceil((unsigned int)(h));
        wsize = (int)bit_ceil((unsigned int)(w));
        data.assign(4*hsize*wsize,e());
    }
    segtree2d(const vector<vector<S>> &v): h(int(v.size())), w(int(v[0].size())) {
        hsize = (int)bit_ceil((unsigned int)(h));
        wsize = (int)bit_ceil((unsigned int)(w));
        data = vector<S>(4*hsize*wsize,e());
        for(int i=0; i<h; i++)for(int j=0; j<w; j++) inner_set(i,j,v[i][j]);
        build();
    }

    void inner_set(int r, int c, S x){
        assert(0<=r&&r<h);
        assert(0<=c&&c<w);
        data[id(r+hsize,c+wsize)] = x;
    }

    void build(){
        for(int c=wsize; c<2*wsize; c++){
            for(int r=hsize-1; r; r--){
                data[id(r,c)] = op(data[id(2*r,c)], data[id(2*r+1,c)]);
            }
        }
        for(int r=0; r<2*hsize; r++){
            for(int c=wsize-1; c; c--){
                data[id(r,c)] = op(data[id(r,2*c)], data[id(r,2*c+1)]);
            }
        }
    }

    S get(int r, int c){
        assert(0<=r&&r<h);
        assert(0<=c&&c<w);
        return data[id(r+hsize,c+wsize)];
    }

    S inner_prod(int l, int r1, int r2){
        S res = e();
        for(; r1<r2; r1>>=1, r2>>=1){
            if(r1&1) res = op(res, data[id(l,r1)]), r1++;
            if(r2&1) --r2, res = op(res, data[id(l,r2)]);
        }
        return res;
    }

    S prod(int i1, int j1, int i2, int j2) {
        assert(0<=i1 && i1<h && 0<=i2 && i2<=h);
        assert(0<=j1 && j1<w && 0<=j2 && j2<=w);
        if(i1>=i2 || j1>=j2) return e();
        S res = e();
        i1 += hsize; i2 += hsize;
        j1 += wsize; j2 += wsize;
        for(;i1<i2; i1>>=1, i2>>=1){
            if(i1&1) res = op(res,inner_prod(i1,j1,j2)), i1++;
            if(i2&1) --i2, res = op(res,inner_prod(i2,j1,j2));
        }
        return res;
    }

    void set(int r, int c, S x){
        r+=hsize; c+=wsize;
        data[id(r,c)] = x;
        for(int i=r>>1; r; r>>=1){
            data[id(i,c)] = op(data[id(2*i,c)], data[id(2*i+1,c)]);
        }
        for(; r; r>>=1){
            for(int j=c>>1; c; c>>=1){
                data[id(r,j)] = op(data[id(r,2*j)], data[id(r,2*j+1)]);
            }
        }
    }

    void print(int i1, int j1, int i2, int j2){
        assert(0<=i1 && i1<h && 0<=i2 && i2<=h);
        assert(0<=j1 && j1<w && 0<=j2 && j2<=w);
        if(i1==i2 || j1==j2){
            cerr << "Area is 0" << endl;
            return;
        }
        for(int i=i1; i<i2; i++){
            for(int j=j1; j<j2; j++) cerr << data[id(i+hsize,j+wsize)] << " ";
            cerr << endl;
        }
    }
};
using S = ll;
const ll INF = 8e18;

S op(S a, S b){ return min(a,b); };
S e() { return INF; }

void AOJ1068(){
    while(1){
        int r,c,q; cin >> r >> c >> q;
        if(r==0) break;
        vector g(r,vector<S>(c));
        for(int i=0; i<r; i++)for(int j=0; j<c; j++){
            cin >> g[i][j];
        }
        segtree2d<S,op,e> seg(g);
        for(;q--;){
            int r1,c1,r2,c2;
            cin >> r1 >> c1 >> r2 >> c2;
            cout << seg.prod(r1,c1,r2+1,c2+1) << endl;
        }
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    AOJ1068();
}