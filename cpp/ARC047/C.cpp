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
    int n, k;
    cin >> n >> k;
    int f = 1;
    REP(i, n) f *= i+1;
    assert(f % k == 0);
    f /= k;
    vector<int> ans(n);
    REP(i, n) ans[i] = i + 1;
    REP(_, f) {
        next_permutation(ans.begin(), ans.end());
    }
    REP(i, ans.size()) cout << ans[i] << " ";cout << endl;
    return 0;
}

