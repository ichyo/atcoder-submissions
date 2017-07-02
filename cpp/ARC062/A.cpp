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
    while(cin >> N) {
        LL A, B;
        REP(i, N) {
            LL x, y;
            cin >> x >> y;
            if(i == 0) {
                A = x;
                B = y;
            } else {
                LL k = max((A + x - 1) / x, (B + y - 1) / y);
                A = k * x;
                B = k * y;
            }
        }
        cout << (A + B) << endl;
    }
    return 0;
}
