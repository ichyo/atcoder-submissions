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
        vector<LL> a(N);
        REP(i, N) cin >> a[i];
        LL ans = LLONG_MAX;
        REP(iter, 2){
            LL result = 0;
            LL s = 0;
            REP(i, N) {
                s += a[i];
                bool plus = ((iter + i) % 2 == 0);
                if(plus) {
                    if(s <= 0) {
                        result += abs(1 - s);
                        // cerr << i << " " << s << " " << 1 << endl;
                        // cerr << result << endl;
                        s = 1;
                    }
                } else {
                    if(s >= 0) {
                        result += abs(s + 1);
                        // cerr << i << " " << s << " " << -1 << endl;
                        // cerr << result << endl;
                        s = -1;
                    }
                }
            }
            // cerr << "end: " << result << endl;
            ans = min(ans, result);
        }
        cout << ans << endl;
    }
    return 0;
}

