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
    int N, X;
    while(cin >> N >> X) {
    LL ans = 0;
    vector<int> A(N);
    REP(i, N) cin >> A[i];
    REP(i, N) {
        if(A[i] > X) {
            LL diff = A[i] - X;
            ans += diff;
            A[i] -= diff;
        }
        if(i-1 >= 0) {
            LL diff = (A[i] + A[i-1]) - X;
            if(diff > 0) {
                assert(A[i] >= diff);
                ans += diff;
                A[i] -= diff;
            }
        }
    }
    cout << ans << endl;
    }
    return 0;
}

