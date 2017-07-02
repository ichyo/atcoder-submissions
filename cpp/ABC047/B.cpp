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
    int W, H, N;
    cin >> W >> H >> N;
    pair<int, int> XS(0, W);
    pair<int, int> YS(0, H);
    while(N--) {
        int x, y, t;
        cin >> x >> y >> t;
        if(t == 1) {
            XS.first = max(XS.first, x);
        } else if(t == 2) {
            XS.second = min(XS.second, x);
        } else if(t == 3) {
            YS.first = max(YS.first, y);
        } else {
            YS.second = min(YS.second, y);
        }
    }

    int width = max(0, XS.second - XS.first);
    int height = max(0, YS.second - YS.first);
    cout << width * height << endl;
    return 0;
}

