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
int N, K;
Graph G;
map<int, int> value;
const int MAX_N = 100000;
int parent[MAX_N];
vector<int> child[MAX_N];
void dfs(int r, int p) {
    parent[r] = p;
    for(int c : G[r]) {
        if(c != p) {
            child[r].push_back(c);
            dfs(c, r);
        }
    }
}
void build_rooted_tree(int root) {
    REP(i, N) child[i].clear();
    dfs(root, -1);
}

int ub[MAX_N];
int lb[MAX_N];
void set_bound(int v) {
    for(int c : child[v]) {
        set_bound(c);
    }
    if(value.count(v)) {
        lb[v] = ub[v] = value[v];
    } else {
        for(int c : child[v]) {
            if(lb[c] > INT_MIN) {
                lb[v] = max(lb[v], lb[c]-1);
            }
            if(ub[c] < INT_MAX) {
                ub[v] = min(ub[v], ub[c]+1);
            }
        }
    }
}

int main(){
    iostream_init();

    while(cin >> N) {
        G.assign(N, Node());

        REP(i, N-1) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            G[a].push_back(b);
            G[b].push_back(a);
        }

        value.clear();
        cin >> K;
        REP(i, K) {
            int v, p;
            cin >> v >> p;
            v--;
            value[v] = p;
        }

        const int root = value.begin()->first;
        build_rooted_tree(root);

        REP(i, N) ub[i] = INT_MAX;
        REP(i, N) lb[i] = INT_MIN;
        set_bound(root);

        bool valid = true;
        int answer[MAX_N] = {};
        answer[root] = value[root];
        queue<int> que;
        for(int c : child[root]) que.push(c);
        while(!que.empty()) {
            const int v = que.front(); que.pop();
            const int parent_val = answer[ parent[v] ];
            bool is_set = false;
            for(int d = -1; d <= 1; d += 2) {
                const int next_val = parent_val + d;
                if(lb[v] <= next_val && next_val <= ub[v]) {
                    answer[v] = next_val;
                    is_set = true;
                    for(int c : child[v]) que.push(c);
                    break;
                }
            }
            if(!is_set) {
                valid = false;
                break;
            }
        }
        if(valid) {
            cout << "Yes" << endl;
            REP(i, N) {
                cout << answer[i] << endl;
            }
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}
