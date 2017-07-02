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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
inline bool valid(int x, int w) { return 0 <= x && x < w; }

void iostream_init() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
//}}}

typedef long long LL;
const LL MOD = 1000000007;
const int MAX_P = 100010;
LL inv[MAX_P];
LL fact[MAX_P], rfact[MAX_P];
void init(){
    inv[1] = 1;
    for (LL i = 2; i < MAX_P; ++i){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    }
    fact[0] = rfact[0] = 1;
    for(LL i = 1; i < MAX_P; i++){
        fact[i] = ((LL)fact[i - 1] * i) % MOD;
        rfact[i] = ((LL)rfact[i - 1] * inv[i]) % MOD;
    }
}
LL comb(int n, int k){
    if(n < k) return 0;
    assert(k >= 0);
    if(k < 0) return 0;
    return (((LL)fact[n] * rfact[n - k]) % MOD) * rfact[k] % MOD;
}
const int H = 3010;
const int W = 3010;
int grid[H][W] = {};
int acum[H+10][W+10] = {};
int get(int x1, int x2, int y1, int y2) {
    return acum[y2][x2] - acum[y2][x1] - acum[y1][x2] + acum[y1][x1];
}
int main(){
    iostream_init();
    init();

    int N, K;
    while(cin >> N >> K) {
#ifdef LOCAL
        memset(grid, 0, sizeof(grid));
#endif
        vector<int> X(N);
        vector<int> Y(N);
        REP(i, N) {
            cin >> X[i] >> Y[i];
            int x = X[i];
            int y = Y[i];
            grid[y][x]++;
        }
#ifdef LOCAL
        memset(acum, 0, sizeof(acum));
#endif
        REP(y, H) REP(x, W) {
            acum[y+1][x+1] = acum[y+1][x] + acum[y][x+1] - acum[y][x] + grid[y][x];
        }

        int lb = 0, ub = H-1;
        // (lb, ub]
        while(ub - lb > 1) {
            int L = (lb + ub) / 2;

            bool ok = false;
            REP(y, H-L+1) REP(x, W-L+1) {
                int sum = acum[y+L][x+L] - acum[y][x+L] - acum[y+L][x] + acum[y][x];
                if(sum >= K) {
                    ok = true;
                    goto UPDATE;
                }
            }
UPDATE:
            if(ok) {
                ub = L;
            } else {
                lb = L;
            }
        }

        int S = ub-1;
        int L = S+1;
        cout << S << endl;

        LL ans = 0;
        REP(y, H-L+1) REP(x, W-L+1) {
            int sumlu = grid[y][x];
            int suml  = get(x, x+1, y, y+L) - sumlu;
            int sumu  = get(x, x+L, y, y+1) - sumlu;
            int sumex = get(x, x+L, y, y+L) - suml - sumu - sumlu;
            int all = sumlu + suml + sumu + sumex;
            assert(all == get(x, x+L, y, y+L));
            if(all < K) continue;

            // for(int k = 1; k <= sumlu && k <= K; k++) {
            //     int rest = all - sumlu;
            //     if(rest + k < K) continue;
            //     // rest -> K - k
            //     ans += comb(sumlu, k) * comb(rest, K-k);
            //     ans %= MOD;
            // }

            ans += comb(all, K) - comb(all-sumlu, K);
            ans += 2*MOD;
            ans %= MOD;
            
            if(suml > 0 && sumu > 0 && all-sumlu >= K) {
                ans += comb(all-sumlu, K);
                ans %= MOD;
                if(all - sumlu - suml >= K) {
                    ans += MOD - comb(all-sumlu-suml, K);
                    ans %= MOD;
                }
                if(all - sumlu - sumu >= K) {
                    ans += MOD - comb(all-sumlu-sumu, K);
                    ans %= MOD;
                }
                if(sumex >= K) {
                    assert(sumex == all - sumlu - sumu - suml);
                    ans += comb(sumex, K);
                    ans %= MOD;
                }
            }
            // ans += comb(all, K);
            // ans %= MOD;
            // int xx = get(x+1, x+L, y, y+L);
            // int yy = get(x, x+L, y+1, y+L);
            // ans += MOD - comb(xx, K);
            // ans %= MOD;
            // ans += MOD - comb(yy, K);
            // ans %= MOD;
        }
        cout << ans << endl;
    }
    

    return 0;
}

/* vim:set foldmethod=marker: */

