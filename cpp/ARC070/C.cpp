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

int main(){
    iostream_init();
    int N;
    while(cin >> N) {
        assert(N <= 400);
        const int MAX_N = 402;
        const int MAX_L = 802;
        int dp[MAX_N][MAX_L] = {};
        REP(i, MAX_N) REP(j, MAX_L) dp[i][j] = INT_MAX / 2 - 1;
        vector<int> L(N), R(N);
        vector<int> W(N);
        REP(i, N){
            cin >> L[i] >> R[i];
            assert(L[i] <= 400);
            assert(R[i] <= 400);
        }
        REP(i, N) W[i] = R[i] - L[i];

        REP(i, N) {
            REP(f, MAX_L) REP(t, MAX_L) {
                if(i == 0 || !(f + W[i-1] < t || t + W[i] < f)) {
                    int last = (i == 0 ? 0 : dp[i-1][f]);
                    dp[i][t] = min(dp[i][t], last + abs(t - L[i]));
                }
            }
            int first = INT_MAX;
            int last = INT_MIN;
            REP(t, MAX_L-1){
                int diff = dp[i][t+1] - dp[i][t];
                if(diff >= 0) {
                    first = min(first, t);
                    if(first == t) last = t;
                    if(diff == 0) {
                        last = t;
                    }
                }
            }
            cout << first;
            if(last != first) cout << " " << last;
            cout << " " << "[" << L[i] << "," << R[i] << "]" << "-> [" << first << "," << first + W[i] << "]";
            cout << endl;

        }

        int ans = 1e9;
        REP(i, MAX_L) ans = min(ans, dp[N-1][i]);
        cout << ans << endl;
    }
    return 0;
}

