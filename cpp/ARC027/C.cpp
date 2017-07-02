#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int X, Y;
    int N;
    while(cin >> X >> Y >> N) {
        typedef long long LL;
        LL dp[303][303] = {};
        REP(i, X + 1) REP(j, Y + 1) dp[i][j] = LLONG_MIN;
        dp[X][Y] = 0;
        for(int i = 0; i < N; i++) {
            LL next[303][303] = {};
            REP(i, X + 1) REP(j, Y + 1) next[i][j] = LLONG_MIN;
            int t;
            LL h;
            cin >> t >> h;
            for(int x = 1; x <= X; x++) {
                for(int y = 0; y <= Y; y++) {
                    if(dp[x][y] < 0) continue;
                    int nx = x - 1;
                    int rest = t - 1;
                    int use = min(rest, y);
                    int ny = y - use;
                    rest -= use;
                    nx -= rest;
                    if(nx < 0) continue;
                    next[nx][ny] = max(next[nx][ny], dp[x][y] + h);
                }
            }
            REP(x, X + 1) REP(y, Y + 1) dp[x][y] = max(dp[x][y], next[x][y]);
        }
        LL ans = 0;
        REP(i, X + 1) REP(j, Y + 1) ans = max(dp[i][j], ans);
        cout << ans << endl;
    }
    return 0;
}

