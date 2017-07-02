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

map<pair<int, int>, bool> memo;
bool dfs(int X, int Y) {
    if(X <= 1 && Y <= 1) { return false; }
    if(X > Y) { return dfs(Y, X); }
    auto state = make_pair(X, Y);
    if(memo.count(state)) { return memo[state]; }
    for(int i = 1; 2*i <= X; i++) {
        if(!dfs(X-2*i, Y+i)) {
            return memo[state] = true;
        }
    }
    for(int i = 1; 2*i <= Y; i++) {
        if(!dfs(X+i, Y-2*i)) {
            return memo[state] = true;
        }
    }
    return memo[state] = false;
}
int main(){
    iostream_init();
    // for(int x = 1; x <= 10; x++) {
    //     for(int y = 1; y <= 10; y++) {
    //         cout << x << " " << y << " = " << dfs(x, y) << endl;
    //     }
    // }
    // for(int x = 1; x <= 30; x++) {
    //     for(int y = 1; y <= 30; y++) {
    //         cout << dfs(x, y) ? 1 : 0;
    //         cout << " ";
    //     }
    //     cout << endl;
    // }
    LL X, Y;
    cin >> X >> Y;
    if(X < 10 && Y < 10) {
        cout << (dfs(X, Y) ? "Alice" : "Brown") << endl;
    } else if(abs(X - Y) > 1) {
        cout << "Alice" << endl;
    } else {
        cout << "Brown" << endl;
    }
    return 0;
}

