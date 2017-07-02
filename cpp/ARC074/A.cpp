// Template {{{
#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

#ifdef LOCAL
#include "contest.h"
#else
#define error(args...) 
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

LL rest(LL H, LL W, LL S) {
    LL S1 = (H/2) * W;
    LL S2 = (H - (H/2)) * W;
    LL T1 = (W/2) * H;
    LL T2 = (W - W/2) * H;
    return min(max({S1, S2, S}) - min({S1, S2, S}),
               max({T1, T2, S}) - min({T1, T2, S}));
}
int main(){
    iostream_init();
    LL H, W;
    cin >> H >> W;
    LL ans = LLONG_MAX;
    for(LL h1 = 1; h1 < H; h1++) {
        LL s = h1 * W;
        ans = min(ans, rest(H-h1, W, s));
    }
    for(LL w1 = 1; w1 < W; w1++) {
        LL s = w1 * H;
        ans = min(ans, rest(H, W-w1, s));
    }
    cout << ans << endl;
    return 0;
}

