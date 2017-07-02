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

typedef vector<int> Node;
typedef vector<Node> Graph;

Graph G;
vector<int> X;

vector<int> color[2];
int memo[2][100000];
int depth[2][100000];
int value[100000];
const int MAX = 1000000001;
int dfs(int u, int turn, int d) {
    if(color[turn][u] == 1) {
        int first = depth[turn][u] / 2;
        int loop = (d - depth[turn][u]) / 2;
        loop = (MAX-first) % loop;
        return value[first * 2 + loop * 2];
    } else if(color[turn][u] == 2) {
        return memo[turn][u];
    } else {
        color[turn][u] = 1;
        depth[turn][u] = d;
        value[d] = X[u];

        int& res = memo[turn][u];
        if(turn == 0) {
            res = X[u];
            for(int v : G[u]) {
                res = max(res, dfs(v, turn^1, d+1));
            }
        } else {
            res = X[u];
            for(int v : G[u]) {
                res = min(res, dfs(v, turn^1, d+1));
            }
        }
        color[turn][u] = 2;
        return res;
    }
}

int main(){
    iostream_init();
    int N, M;
    while(cin >> N >> M) {
        X.resize(N);
        REP(i, 2) color[i].assign(N, 0);
        REP(i, N) cin >> X[i];
        G.assign(N, Node());
        REP(i, M) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            G[a].push_back(b);
        }
        cout << dfs(0, 0, 0) << endl;
    }
    return 0;
}

/* vim:set foldmethod=marker: */

