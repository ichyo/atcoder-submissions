#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;
int h[101];
typedef vector<int> Node;
typedef vector<Node> Graph;
Graph G;
pair<int, bool> dfs(int u, int p) {
    int ans = 0;
    bool exist = h[u];
    for(int v : G[u]) if(v != p) {
        auto res = dfs(v, u);
        if(res.second) res.first += 2;
        ans += res.first;
        exist = exist || res.second;
    }
    return make_pair(ans, exist);
}

int main(){
    int n, x;
    while(cin >> n >> x){
        x--;
        REP(i, n) cin >> h[i];
        G.assign(n, Node());
        REP(i, n - 1) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        auto p = dfs(x, -1);
        cout << p.first << endl;
    }
    return 0;
}

