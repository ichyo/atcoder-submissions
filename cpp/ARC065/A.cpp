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
    vector<bool> a(n+1, false);
    a[0] = true;
    vector<string> v = {
        "dream",
        "dreamer",
        "erase",
        "eraser"
    };

    REP(i, s.size()) {
        if(a[i]) {
            for(auto t : v) {
                int ni = i + t.size();
                if(ni <= n && s.substr(i, t.size()) == t) {
                    a[ni] = true;
                }
            }
        }
    }
    cout << (a[n] ? "YES" : "NO") << endl;
    return 0;
}

