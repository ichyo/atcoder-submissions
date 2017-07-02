#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

typedef long long LL;
typedef vector<LL> Array;
typedef vector<Array> Matrix;

LL MOD = 1000000000 + 7;

// 行列の掛け算 O(N * M * S)
Matrix mul(const Matrix& a, const Matrix& b){
    int N = a.size(), M = b[0].size(), S = a[0].size();
    assert(S == b.size());
    Matrix c(N, Array(M));
    for(int i = 0; i < N; i++){
        for(int k = 0; k < S; k++){
            for(int j = 0; j < M; j++){
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= MOD;
            }
        }
    }
    return c;
}
// 正方行列の累乗 O(N^3 * logn)
Matrix pow(Matrix a, LL b){
    int N = a.size();
    Matrix c(N, Array(N));
    REP(i, N) c[i][i] = 1;
    while(b > 0){
        if(b & 1) c = mul(c, a);
        a = mul(a, a);
        b >>= 1;
    }
    return c;
}


int main(){
    int H;
    LL W;
    while(cin >> H >> W) {
        int N;
        cin >> N;
        if(H == 1) {
            assert(N <= 3000);
            Matrix A = {
                {1, 1},
                {1, 0}
            };
            Matrix Z = {
                {1, 0},
                {0, 0}
            };
            set<LL> s;
            for(int i = 0; i < N; i++){
                int y;
                LL x;
                cin >> y >> x;
                if(s.count(x)) {
                    s.erase(s.find(x));
                } else {
                    s.insert(x);
                }
                LL last = 1;
                Matrix B = {
                    {1, 0},
                    {0, 1}
                };
                for(LL cur : s) {
                    B = mul(pow(A, cur - last), B);
                    B = mul(Z, B);
                    last = cur + 1;
                }
                if(last < W) {
                    B = mul(pow(A, W - last), B);
                }
                cout << (B[0][0] + B[1][0]) % MOD << endl;
            }
        } else if(H == 2) {
            Matrix A = {
                {1, 1, 1, 1}, // 00
                {1, 0, 1, 0}, // 01
                {0, 1, 0, 1}, // 10
                {2, 1, 1, 1}  // 11
            };
            Matrix Z1 = {
                {1, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 0}
            };
            Matrix Z2 = {
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            };
            map<LL, int> m;
            for(int i = 0; i < N; i++){
                int y;
                LL x;
                cin >> y >> x;
                m[x] ^= 1 << (y - 1);
                if(m[x] == 0) {
                    m.erase(m.find(x));
                }
                LL last = 1;
                Matrix B = {
                    {1, 0, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}
                };
                for(auto p : m) {
                    LL x = p.first;
                    int s = p.second;
                    assert(s != 0);
                    B = mul(pow(A, x - last), B);
                    if(s & 1) B = mul(Z1, B);
                    if(s >> 1 & 1) B = mul(Z2, B);
                    if(s == 1) {
                        Matrix C = {
                            {1, 1, 1, 1}, // 00
                            {0, 0, 0, 0}, // 01
                            {0, 1, 0, 1}, // 10
                            {1, 1, 1, 1}  // 11
                        };
                        B = mul(C, B);
                    } else if(s == 2) {
                        Matrix C = {
                            {1, 1, 1, 1}, // 00
                            {1, 0, 1, 0}, // 01
                            {0, 0, 0, 0}, // 10
                            {1, 1, 1, 1}  // 11
                        };
                        B = mul(C, B);
                    } else if(s == 3) {
                        Matrix C = {
                            {1, 1, 1, 1}, // 00
                            {0, 0, 0, 0}, // 01
                            {0, 0, 0, 0}, // 10
                            {0, 0, 0, 0}  // 11
                        };
                        B = mul(C, B);
                    }
                    last = x + 1;
                }
                if(last < W) {
                    B = mul(pow(A, W - last), B);
                }
                LL ans = 0;
                for(int i = 0; i < 4; i++){
                    ans = (ans + B[i][0]) % MOD;
                    if(!m.count(1))
                        ans = (ans + B[i][3]) % MOD;
                }
                cout << ans << endl;
            }
        }
    }
    return 0;
}

