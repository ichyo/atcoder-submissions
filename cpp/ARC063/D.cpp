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
    int W, H;
    
    int N;
    while(cin >> W >> H >> N) {
        vector<pair<int, int>> ps(N);
        REP(i, N) cin >> ps[i].first >> ps[i].second;
        sort(ps.begin(), ps.end());

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j += 10) {
            }
        }

    }
    return 0;
}
