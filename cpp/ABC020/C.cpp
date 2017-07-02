// Template {{{
#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

template<typename T1, typename T2>
ostream& operator << (ostream& os, const pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream& os, const vector<T>& v) {
    os << "{";
    for(int i = 0; i < v.size(); i++)
        os << v[i] << (i+1<v.size()?", ":"");
    os << "}";
    return os;
}

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
    int H, W, T;
    while(cin >> H >> W >> T) {
        vector<string> grid(H);
        REP(y, H) cin >> grid[y];
        int sx, sy, gx, gy;
        REP(y, H) REP(x, W) if(grid[y][x] == 'S') { sx = x; sy = y; }
        REP(y, H) REP(x, W) if(grid[y][x] == 'G') { gx = x; gy = y; }

        // [lb, ub)
        int lb = 1, ub = T;
        while(ub-lb > 1) {
            int M = (lb+ub)/2;
            int dist[10][10] = {};
            REP(y, H) REP(x, W) dist[y][x] = T+1;

            queue<int> qx, qy;
            qx.push(sx);
            qy.push(sy);
            dist[sy][sx] = 0;

            while(!qx.empty()) {
                int x = qx.front(); qx.pop();
                int y = qy.front(); qy.pop();
                int d = dist[y][x];
                REP(r, 4) {
                    int nx = x+dx[r];
                    int ny = y+dy[r];
                    if(valid(nx, W) && valid(ny, H)) {
                        int nd = d + (grid[ny][nx] == '#' ? M : 1);
                        if(dist[ny][nx] > nd) {
                            dist[ny][nx] = nd;
                            qx.push(nx);
                            qy.push(ny);
                        }
                    }
                }
            }

            if(dist[gy][gx] <= T) {
                lb = M;
            } else {
                ub = M;
            }
        }
        cout << lb << endl;
    }
    return 0;
}

/* vim:set foldmethod=marker: */

