//
// 行列の基本演算
//
/*



*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0; i<(n); i++)
#define all(x) (x).begin(), (x).end()
using ll = long long;
using P = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vi>;

template<typename T>
struct mat{
    //初期化
    vector<vector<T>> m;
    mat():m(vector<vector<T>>()){}
    mat(int h, int w):m(vector<vector<T>>(h,vector<T>(w))){}

    vector<T> operator[](const int i) const {return m[i];}
    vector<T>& operator[](const int i) {return m[i];}

    int h = m.size();
    int w = m[0].size();

    //基本演算
    mat& operator=(const mat& a){return *a;}
    mat& operator+=(const mat& a) {
        assert(h==a.h && w==a.w);
        rep(i,h)rep(j,w) m[i][j]+=a[i][j]; return *this;
    }
    mat& operator-=(const mat& a) {
        assert(h==a.h && w==a.w);
        rep(i,h)rep(j,w) m[i][j]-=a[i][j]; return *this;
    }
    mat& operator*=(const mat& a) {
        assert(w==a.h); mat<T> m2(h,a.w);
        rep(i,h)rep(j,a.w)rep(k,w) m2[i][j]+=m[i][k]*a[k][j];
        w=a.w; rep(i,h) m[i].resize(w);
        rep(i,h)rep(j,w) m[i][j]=m2[i][j]; return *this;
    }
    mat operator+(const mat& a) const {return mat(*this)+=a;}
    mat operator-(const mat& a) const {return mat(*this)-=a;}
    mat operator*(const mat& a) const {return mat(*this)*=a;}
    bool operator==(const mat& a){
        assert(h==a.h && w==a.w);
        rep(i,h)rep(j,w) if(m[i][j]!=a[i][j]) return false;
        return true;
    }
    //スカラ演算
    mat& operator+=(const T& a){rep(i,h)rep(j,w)m[i][j]+=a; return *this;}
    mat& operator-=(const T& a){rep(i,h)rep(j,w)m[i][j]-=a; return *this;}
    mat& operator*=(const T& a){rep(i,h)rep(j,w)m[i][j]*=a; return *this;}
    mat& operator/=(const T& a){rep(i,h)rep(j,w)m[i][j]/=a; return *this;}
    mat operator+(const T& a) const {return mat(*this)+=a;}
    mat operator-(const T& a) const {return mat(*this)-=a;}
    mat operator*(const T& a) const {return mat(*this)*=a;}
    mat operator/(const T& a) const {return mat(*this)/=a;}
    //転置（必要になったら追加）

    //出力
    void show(){
        rep(i,h)rep(j,w){
            if(j==0) cout << m[i][j];
            else cout << " " << m[i][j];
            if(j==w-1) cout << "\n";
        }
        return;
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    mat<int> m(3,3), n(3,2);
    m+=1; n+=2;
    m.show();

    m*=n;
    m.show();
}