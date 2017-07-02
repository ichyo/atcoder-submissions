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
    string s;
    cin >> s;
    int n = s.size();
    int ans1=-1, ans2=-1;
    REP(i, n-1) {
        if(s[i] == s[i+1]) {
            ans1 = i+1;
            ans2 = i+2;
            break;
        }
    }
    if(ans1 == -1) {
        REP(i, n-2) {
            if(s[i] == s[i+2]) {
                ans1 = i+1;
                ans2 = i+3;
                break;
            }
        }
    }
    cout << ans1 << " " << ans2 << endl;
    return 0;
}

