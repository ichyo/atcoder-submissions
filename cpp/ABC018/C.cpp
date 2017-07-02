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
}
//}}}

int main(){
    iostream_init();

    int H, W, K;
    while(cin >> H >> W >> K){
        vector<string> grid(H);
        REP(y, H) cin >> grid[y];
        int sum[505][505] = {};
        REP(y, H) {
            sum[y][0] = 0;
            REP(x, W) {
                sum[y][x+1] = sum[y][x] + (grid[y][x] == 'o' ? 1 : 0);
            }
        }

        int ans = 0;
        REP(y, H) if(y - (K - 1) >= 0 && y + (K - 1) < H) {
            REP(x, W) if(x - (K - 1) >= 0 && x + (K - 1) < W) {
                bool ok = true;
                for(int dy = -(K-1); dy <= K-1; dy++) {
                    int abx = (K-1) - abs(dy);
                    // [x - abx, x + abx]
                    // 2 * abx + 1
                    int calc = sum[y + dy][x + abx + 1] - sum[y+dy][x-abx];
                    if(calc < 2 * abx + 1) ok = false;
                }
                if(ok) ans++;
            }
        }

        cout << ans << endl;
    }

    return 0;
}

/* vim:set foldmethod=marker: */

