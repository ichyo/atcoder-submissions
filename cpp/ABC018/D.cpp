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

    int N, M, P, Q, R;
    while(cin >> N >> M >> P >> Q >> R) {
        vector<int> to[18];
        vector<int> cost[18];
        REP(i, R) {
            int x, y, z;
            cin >> x >> y >> z;
            x--; y--; 
            to[x].push_back(y);
            cost[x].push_back(z);
        }

        int ans = 0;
        for(int comb = (1 << P) - 1; comb < (1 << N);){
            int get[18] = {};
            REP(i, N) if(comb >> i & 1) {
                REP(j, to[i].size()) {
                    get[ to[i][j] ] += cost[i][j];
                }
            }
            sort(get, get + M);
            reverse(get, get + M);
            int sub = 0;
            REP(i, Q) sub += get[i];
            ans = max(ans, sub);

            // do something here
            int x = comb & -comb, y = comb + x;
            comb = ((comb & ~y) / x >> 1) | y;
        }

        cout << ans << endl;
    }

    return 0;
}

/* vim:set foldmethod=marker: */

