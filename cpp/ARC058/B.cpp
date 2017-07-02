// Template {{{
#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

#ifdef LOCAL
#include "contest.h"
#else
#define dump(x) 
#endif

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
inline bool valid(int x, int w) { return 0 <= x && x < w; }

void iostream_init() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.setf(ios::fixed);
    cout.precision(12);
}
//}}}

const int MAX_P = 200010;
LL inv[MAX_P];
LL MOD = 1000000000 + 7;
int fact[MAX_P], rfact[MAX_P];
void init(){
    inv[1] = 1;
    for (int i = 2; i < MAX_P; ++i){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    }
    fact[0] = rfact[0] = 1;
    for(int i = 1; i < MAX_P; i++){
        fact[i] = ((LL)fact[i - 1] * i) % MOD;
        rfact[i] = ((LL)rfact[i - 1] * inv[i]) % MOD;
    }
}
LL comb(int n, int k){
    return (((LL)fact[n] * rfact[n - k]) % MOD) * rfact[k] % MOD;
}
LL C(int W, int H) {
    return comb(W + H, W);
}
int main(){
    iostream_init();
    init();
    int W, H, A, B;
    while(cin >> H >> W >> A >> B) {
        LL answer = 0;
        for(int y = 0; y < H - A; y++) {
            answer += C(B-1, y) * C(W-B-1, H-1-y) % MOD;
            answer %= MOD;
        }
        cout << answer << endl;
    }
    return 0;
}

