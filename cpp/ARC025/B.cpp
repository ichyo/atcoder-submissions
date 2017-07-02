#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int H, W;
    while(cin >> H >> W){
        int a[100][100] = {};
        int b[100][100] = {};
        REP(y, H) REP(x, W){
            if((y + x) % 2 == 0) cin >> a[y][x];
            else cin >> b[y][x];
        }
        int sa[101][101] = {};
        int sb[101][101] = {};
        REP(y, H) REP(x, W) {
            sa[y + 1][x + 1] = sa[y][x + 1] + sa[y + 1][x] - sa[y][x] + a[y][x];
            sb[y + 1][x + 1] = sb[y][x + 1] + sb[y + 1][x] - sb[y][x] + b[y][x];
        }
        int res = 0;
        REP(y, H) REP(x, W) {
            for(int dy = 0; y + dy < H; dy++)
            for(int dx = 0; x + dx < W; dx++){
                int y2 = y + dy;
                int x2 = x + dx;
                int suma = sa[y2 + 1][x2 + 1] - sa[y2 + 1][x] - sa[y][x2 + 1] + sa[y][x];
                int sumb = sb[y2 + 1][x2 + 1] - sb[y2 + 1][x] - sb[y][x2 + 1] + sb[y][x];
                if(suma == sumb) {
                    res = max(res, (dx + 1) * (dy + 1));
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}

