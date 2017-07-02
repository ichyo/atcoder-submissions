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

class range {
    struct Iterator {
        int val, inc;
        int operator*() {return val;}
        bool operator!=(Iterator& rhs) {return val < rhs.val;}
        void operator++() {val += inc;}
    };
    Iterator i, n;
    public:
    range(int e) : i({0, 1}), n({e, 1}) {}
    range(int b, int e) : i({b, 1}), n({e, 1}) {}
    range(int b, int e, int inc) : i({b, inc}), n({e, inc}) {}
    Iterator& begin() {return i;}
    Iterator& end() {return n;}
};

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
        vector<int> h(N);
        REP(i, N) cin >> h[i];
        int ans = 0;
        REP(i, N) {
            int s = i;
            int t = i;
            while(t+1 < h.size() && h[t] < h[t+1]) t++;
            int u = t;
            while(u+1 < h.size() && h[u] > h[u+1]) u++;
            ans = max(ans, u - s + 1);
            i = max(i, u-1);
        }
        cout << ans << endl;
    }
    return 0;
}

/* vim:set foldmethod=marker: */

