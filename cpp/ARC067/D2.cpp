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

    int N, M;
    cin >> N >> M;

    vector<LL> A(N-1);
    REP(i, N-1) cin >> A[i];

    vector<vector<LL>> BS(N, vector<LL>(M));
    REP(i, N) REP(j, M) cin >> BS[i][j];

    const int MAX_N = 5001;
    set<int> maxT[MAX_N][MAX_N]; // (end, index)

    REP(i, N) maxT[0][0].insert(i);

    LL answer = LLONG_MIN;
    vector<LL> cost(N); // cost[end]
    // -> 
    {
        LL sum = 0;
        REP(i, M) sum += BS[0][i];
        cost[0] = sum;

        vector<int> maxS(M);
        for(int i = 1; i < N; i++) {
            for(int k = 0; k < i; k++) {
                maxT[i][k] = maxT[i-1][k];
            }
            for(int j = 0; j < M; j++) {
                const int mi = maxS[j];
                if(BS[mi][j] <= BS[i][j]) {
                    maxT[i][mi].erase(j);
                    maxT[i][i].insert(j);
                    maxS[j] = i;
                    sum += BS[i][j] - BS[mi][j];
                }
            }
            sum -= A[i-1];
            cost[i] = sum;
        }
    }

    for(auto c : cost) answer = max(answer, c);

    // <-
    for(int e = 1; e < N; e++) {
        for(int b = 1; b <= e; b++) {
            cost[e] += A[b-1];
            for(int t : maxT[e][b-1]) {
                // find new max s
                int new_s = [&]() -> int{
                    // TODO: fast
                    int idx = b;
                    for(int i = b; i <= e; i++) {
                        if(BS[idx][t] <= BS[i][t]) {
                            idx = i;
                        }
                    }
                    return idx;
                }();
            }
        }
    }

    return 0;
}

