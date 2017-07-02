#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool valid(int x, int w) {
    return 0 <= x && x < w;
}

string grid[10];
const int H = 10;
const int W = 10;
void dfs(int x, int y, bool used[10][10]) {
    if(used[y][x]) return;
    used[y][x] = true;
    REP(r, 4) {
        int nx = x + dx[r];
        int ny = y+ dy[r];
        if(valid(nx, W) && valid(ny, H)) {
            if(grid[ny][nx] == 'o') {
                dfs(nx, ny, used);
            }
        }
    }
}
bool check() {
    bool used[10][10] = {};
    REP(y, H) REP(x, W) if(grid[y][x] == 'o') {
        dfs(x, y, used);
        goto END;
    }
END:
    REP(y, H) REP(x, W) if(!used[y][x] && grid[y][x] == 'o') {
        return false;
    }
    return true;
}

int main(){
    REP(y, 10) {
        cin >> grid[y];
    }
    bool ans = false;
    ans |= check();
    REP(y, 10) REP(x, 10) {
        if(grid[y][x] == 'x') {
            grid[y][x] = 'o';
            ans |= check();
            grid[y][x] = 'x';
        } 
    }
    cout << (ans ? "YES" : "NO") << endl;
    return 0;
}

