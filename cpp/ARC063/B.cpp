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

int main(){
    iostream_init();
    int N, T;
    cin >> N >> T;
    vector<int> A(N);
    REP(i, N) cin >> A[i];

    vector<int> min_As(N);
    vector<int> min_indexs(N);
    int min_A = INT_MAX;
    int min_index = -1;
    int max_diff = INT_MIN;
    REP(i, N) {
        if(min_A > A[i]) {
            min_A = A[i];
            min_index = i;
        }
        min_As[i] = min_A;
        min_indexs[i] = min_index;
        max_diff = max(max_diff, A[i] - min_A);
    }

    vector<bool> used(N);
    REP(i, N) {
        if(A[i] - min_As[i] == max_diff) {
            used[min_indexs[i]] = true;
        }
    }

    int ans = 0;
    REP(i, N) ans += used[i];
    cout << ans << endl;

    return 0;
}
