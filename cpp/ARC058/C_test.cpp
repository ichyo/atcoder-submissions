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

int cnt;
int stk[10];
void dfs(int k, int r) {
    if(k == 3) {
        cnt++;
        return;
    }
    for(int x = 1; x <= r; x++) {
        int nr = r - x;
        int nk = k;
        if(nr == 0) {
            nk = nk + 1;
            nr = (k == 1 ? 7 : 5);
        }
        dfs(nk, nr);
    }
}
int main(){
    iostream_init();
    dfs(0, 5);
    cout << cnt << endl;
    return 0;
}

