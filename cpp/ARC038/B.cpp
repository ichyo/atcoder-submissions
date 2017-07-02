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

string grid[100];
int memo[100][100][2];
int H, W;
bool rec(int x, int y, int turn) {
    if(memo[y][x][turn] != -1) return memo[y][x][turn];
    if(turn == 0) {
        if(valid(x+1, W) && grid[y][x+1] != '#') {
            if(rec(x+1, y, turn^1)) return memo[y][x][turn] = true;
        }
        if(valid(y+1, H) && grid[y+1][x] != '#') {
            if(rec(x, y+1, turn^1)) return memo[y][x][turn] = true;
        }
        if(valid(y+1, H) && valid(x+1, W) && grid[y+1][x+1] != '#') {
            if(rec(x+1, y+1, turn^1)) return memo[y][x][turn] = true;
        }
        return memo[y][x][turn] = false;
    } else {
        if(valid(x+1, W) && grid[y][x+1] != '#') {
            if(!rec(x+1, y, turn^1)) return memo[y][x][turn] = false;
        }
        if(valid(y+1, H) && grid[y+1][x] != '#') {
            if(!rec(x, y+1, turn^1)) return memo[y][x][turn] = false;
        }
        if(valid(y+1, H) && valid(x+1, W) && grid[y+1][x+1] != '#') {
            if(!rec(x+1, y+1, turn^1)) return memo[y][x][turn] = false;
        }
        return memo[y][x][turn] = true;
    }
}
int main(){
    iostream_init();
    cin >> H >> W;
    REP(y, H) {
        cin >> grid[y];
    }
    memset(memo, -1, sizeof(memo));
    cout << (rec(0, 0, 0) ? "First" : "Second") << endl;

    return 0;
}

/* vim:set foldmethod=marker: */

