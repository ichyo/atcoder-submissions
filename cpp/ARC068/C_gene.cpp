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
    int N = 3 * 100000;
    int M = 100000;
    cout << N << " " << M << endl;
    REP(i, N) {
HOGE:
        int l = rand() % M + 1;
        int r = rand() % M + 1;
        if(l == r) goto HOGE;
        if(l > r) swap(l, r);
        cout << l << " " << r << endl;
    }

    return 0;
}

