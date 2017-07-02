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

bool slow(string s) {
    if(s.size() == 2) { return false; }
    for(int i = 1; i+1 < s.size(); i++) {
        if(s[i-1] != s[i+1]) {
            if(!slow(s.substr(0, i) + s.substr(i+1))) {
                return true;
            }
        }
    }
    return false;
}

bool wrong2(string s) {
    if(s[0] == s[s.size()-1]) {
        return (s.size()) % 2 == 0;
    }
    int n = s.size();
    int t = 0;
    char A = s[0];
    char B = s[s.size()-1];
    int cnt = 0;
    for(int i = 1; i+1 < s.size(); i++) {
        if(t == 0 && s[i] == B) {
            t = 1;
        } else if(t == 1 && s[i] == A) {
            t = 0;
        } else {
            cnt++;
        }
    }
    if(t == 1) cnt++;
    return cnt % 2 != 0;
}

void dfs(string s, int n, int m) {
    if(s.size() == n) {
        bool w = wrong2(s);
        bool v = slow(s);
        if(w != v) {
            cout << "s: " << s << endl;
            cout << "wrong: " << w << endl;
            cout << "slow: " << v << endl;
            assert(false);
        }
        return;
    }
    REP(i, n) {
        if(s[s.size()-1] != ('a' + i)) {
            dfs(s + (char)('a' + i), n, m);
        }
    }
}

int main(){
    iostream_init();
    string s;
    cin >> s;
    cout << (wrong2(s) ? "First" : "Second") << endl;
    return 0;
}

