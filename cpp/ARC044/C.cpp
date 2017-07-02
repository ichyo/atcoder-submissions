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

typedef vector<int> Node;
typedef vector<Node> Graph;
struct Solver{
    int N;
    Graph G;
    vector<LL> A;
    map<int, LL> get_val;
    LL all;
    void update(int idx, LL v) {
        if(!get_val.count(idx)) get_val[idx] = v;
        if(get_val[idx] > v) get_val[idx] = v;
    }
    LL dfs(int u, int p) {
        LL res = A[u];
        for(int v : G[u]) {
            if(v != p) {
                LL v_get = dfs(v, u);
                LL u_get = all - v_get;
                update(u, u_get);
                update(v, v_get);
                res += v_get;
            }
        }
        return res;
    }

    void run() {
        cin >> N;
        G.resize(N);
        A.resize(N);
        REP(i, N) cin >> A[i];
        REP(i, N-1) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        REP(i, N) all += A[i];

        dfs(0, -1);

        LL max_val = LLONG_MIN;
        REP(i, N) max_val = max(max_val, get_val[i]);
        cout << max_val << endl;
    }
};
int main(){
    iostream_init();
    Solver s;
    s.run();
    return 0;
}

