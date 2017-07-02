// Template {{{
#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

template<typename T1, typename T2>
ostream& operator << (ostream& os, const pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream& os, const vector<T>& v) {
    os << "{";
    for(int i = 0; i < v.size(); i++)
        os << v[i] << (i+1<v.size()?", ":"");
    os << "}";
    return os;
}

class range {
  struct Iterator {
    int val, inc;
    int operator*() {return val;}
    bool operator!=(Iterator& rhs) {return val < rhs.val;}
    void operator++() {val += inc;}
  };
  Iterator i, n;
public:
  range(int e) : i({0, 1}), n({e, 1}) {}
  range(int b, int e) : i({b, 1}), n({e, 1}) {}
  range(int b, int e, int inc) : i({b, inc}), n({e, inc}) {}
  Iterator& begin() {return i;}
  Iterator& end() {return n;}
};

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
inline bool valid(int x, int w) { return 0 <= x && x < w; }

void iostream_init() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
//}}}

static const unsigned MODVAL = 1000000007;
LL extgcd(LL a, LL b, LL& x, LL& y){
    LL d = a;
    if(b != 0){
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }else{
        x = 1; y = 0;
    }
    return d;
}
LL inv_mod(LL a, LL mod){
    LL x, y;
    extgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}
struct mint {
    unsigned val;
    mint():val(0){}
    mint(int      x):val(x%MODVAL) {}
    mint(unsigned x):val(x%MODVAL) {}
    mint(LL       x):val(x%MODVAL) {}
};
mint& operator+=(mint& x, mint y) { return x = x.val+y.val; }
mint& operator-=(mint& x, mint y) { return x = x.val-y.val+MODVAL; }
mint& operator*=(mint& x, mint y) { return x = LL(x.val)*y.val; }
mint& operator/=(mint& x, mint y) { return x = LL(x.val)*inv_mod(y.val, MODVAL); }
mint operator+(mint x, mint y) { return x+=y; }
mint operator-(mint x, mint y) { return x-=y; }
mint operator*(mint x, mint y) { return x*=y; }
mint operator/(mint x, mint y) { return x/=y; }
typedef vector<mint> Vec;
typedef vector<Vec> Mat;
Vec gauss_jordan(const Mat& A, const Vec& b){
    int W = A[0].size();
    int H = A.size();

    Mat B(H, Vec(W + 1));

    for(int y = 0; y < H; y++)
        for(int x = 0; x < W; x++)
            B[y][x] = A[y][x];

    for(int y = 0; y < H; y++)
        B[y][W] = b[y];

    bool unique = true;  // 解が一意かどうか
    int cy = 0; // 現在注目している式

    // 現在注目している変数
    for(int x = 0; x < W; x++){
        int pivot = cy;
        // 注目している変数の係数の絶対値が一番大きい式を選ぶ
        for(int y = cy; y < H; y++){
            if(B[y][x].val > B[pivot][x].val) pivot = y;
        }

        
        if(pivot >= H || B[pivot][x].val == 0) {
            unique = false;
            continue;
        }

        swap(B[cy], B[pivot]);

        // 注目している変数の係数を1にする
        for(int x2 = x + 1; x2 <= W; x2++) {
            B[cy][x2] /= B[cy][x];
        }


        // y番目の式からx2番目の変数を消去
        for(int y = 0; y < H; y++) if(y != cy)
            for(int x2 = x + 1; x2 <= W; x2++)
                B[y][x2] -= B[y][x] * B[cy][x2];

        // 次の式に注目する
        cy++;
    }


    // 解が存在するかどうか
    for(int y = cy; y < H; y++)
        if(B[y][W].val == 0) 
            return Vec();

    // 解が複数存在するかどうか
    if(!unique) return Vec();

    // 一意な解を返す
    Vec V(W);
    int cur_x = 0;
    for(int y = 0; y < H; y++){
        if(B[y][cur_x].val > 0){
            V[cur_x++] = B[y][W];
        }
    }
    return V;
}
int main(){
    iostream_init();
    int N;
    while(cin >> N) {
        N++;
        assert(N <= 200);

        Vec P(N);
        REP(i, N) {
            cin >> P[i].val;
        }
        mint T;
        cin >> T.val;

        Mat mat(N, Vec(N));
        REP(i, N) {
            mint cur = 1;
            REP(j, N) {
                mat[i][j] = cur;
                cur *= i;
            }
        }

        auto res = gauss_jordan(mat, P);
        mint ans = 0;
        mint cur = 1;
        REP(i, N) {
            ans += res[i] * cur;
            cur *= T;
        }
        cout << ans.val << endl;
    }
    return 0;
}

/* vim:set foldmethod=marker: */

