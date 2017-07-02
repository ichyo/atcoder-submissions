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
    int N;
    cin >> N;
    vector<int> A(N);
    REP(i, N) cin >> A[i];
    int ans = INT_MAX;
    for(int X = -100; X <= 100; X++) {
        int sum = 0;
        REP(i, N) {
            int diff = X - A[i];
            sum += diff * diff;
        }
        if(ans > sum) ans = sum;
    }
    cout << ans << endl;
    return 0;
}

