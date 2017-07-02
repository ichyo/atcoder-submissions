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

inline bool valid(int x, int w) { return 0 <= x && x < w; }

void iostream_init() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.setf(ios::fixed);
    cout.precision(12);
}
//}}}
bool grid[10][10];
int ng[10][10];
int counter[10];
int H, W;
int ans;
void dfs(int row) {
    if(row == H) {
        ans++;
        return;
    }

    if(row == H-1) {
        ans += W-counter[row];
        return;
    }

    REP(x, W) {
        if(!grid[row][x] && !ng[row][x]) {
            bool go = true;
            {
                const int dx = -1;
                const int dy = 1;
                int cx = x + dx;
                int cy = row + dy;
                while(valid(cx, W) && valid(cy, H) && !grid[cy][cx]) {
                    ng[cy][cx] ++;
                    if(ng[cy][cx] == 1){
                        counter[cy]++;
                        if(counter[cy] == W) go = false;
                    }
                    cx += dx;
                    cy += dy;
                }
            }
            {
                const int dx = +1;
                const int dy = 1;
                int cx = x + dx;
                int cy = row + dy;
                while(valid(cx, W) && valid(cy, H) && !grid[cy][cx]) {
                    ng[cy][cx] ++;
                    if(ng[cy][cx] == 1){
                        counter[cy]++;
                        if(counter[cy] == W) go = false;
                    }
                    cx += dx;
                    cy += dy;
                }
            }

            if(go) {
                dfs(row + 1);
            }

            {
                const int dx = -1;
                const int dy = 1;
                int cx = x + dx;
                int cy = row + dy;
                while(valid(cx, W) && valid(cy, H) && !grid[cy][cx]) {
                    ng[cy][cx] --;
                    if(ng[cy][cx] == 0){
                        counter[cy]--;
                    }
                    cx += dx;
                    cy += dy;
                }
            }
            {
                const int dx = +1;
                const int dy = 1;
                int cx = x + dx;
                int cy = row + dy;
                while(valid(cx, W) && valid(cy, H) && !grid[cy][cx]) {
                    ng[cy][cx] --;
                    if(ng[cy][cx] == 0){
                        counter[cy]--;
                    }
                    cx += dx;
                    cy += dy;
                }
            }
        }
    }
}
int main(){
    iostream_init();
    cin >> H >> W;

    REP(y, H) {
        string s;
        cin >> s;
        REP(x, W) grid[y][x] = s[x] == '*';
        REP(x, W) if(grid[y][x]) counter[y]++;
    }

    dfs(0);

    cout << ans << endl;

    return 0;
}

