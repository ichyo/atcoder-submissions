#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
typedef long long LL;
typedef vector<int> Array;
typedef vector<Array> Matrix;

const int MOD = 1000000007;

// 行列の掛け算 O(N * M * S)
Matrix mul(const Matrix& a, const Matrix& b){
    int N = a.size(), M = b[0].size(), S = a[0].size();
    assert(S == b.size());
    Matrix c(N, Array(M));
    for(int i = 0; i < N; i++){
        for(int k = 0; k < S; k++){
            for(int j = 0; j < M; j++){
                c[i][j] = (c[i][j] + (long long)a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}
Matrix ID(int N) {
    Matrix M(N, Array(N, 0));
    REP(i, N) M[i][i] = 1;
    return M;
}
vector<Matrix> data;
int M;
Matrix get(int x, int y, int k=1, int l=0, int r=M){
    if (r<=x || y<=l) return ID(10);
    if (x<=l && r<=y) return data[k];
    return mul(get(x, y, k*2+1, (l+r)/2, r), get(x, y, k*2, l, (l+r)/2));
}
int main(){
    int N;
    while(cin >> N) {
        vector<int> h(N);
        REP(i, N) cin >> h[i];
        vector<array<int, 10>> top(N);
        REP(i, N) {
            REP(j, 10){
                int x = i - j - 1;
                if(x >= 0 && h[x] + x >= i) {
                    top[i][j] = 1;
                }
            }
        }
        M = 1;
        while(M < N) M <<= 1;
        data.assign(2 * M + 10, ID(10));
        REP(i, N) {
            REP(k, 10) data[M + i][0][k] = top[i][k];
            REP(j, 9) REP(k, 10){
                data[M + i][j + 1][k] = (j == k ? 1 : 0);
            }
        }
        for(int i = M - 1; i > 0; i--) {
            data[i] = mul(data[2 * i + 1], data[2 * i]);
        }

        int D;
        cin >> D;
        while(D--) {
            int s, t;
            cin >> s >> t;
            Matrix Mat = get(s, t);
            cout << Mat[0][0] << endl;
        }

        // for(int s = 0; s < N; s++) {
        //     for(int t = s + 1; t <= N; t++) {
        //         printf("s = %d t = %d\n", s, t);
        //         Matrix Mat = get(s, t);
        //         REP(i, 10) {
        //             REP(j, 10) cout << Mat[i][j] << " ";
        //             cout << endl;
        //         }
        //         cout << endl;
        //     }
        // }

        // return 0;
    }
    return 0;
}

