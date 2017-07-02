#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

typedef vector<int> Node;
typedef vector<Node> Graph;
Graph G;
vector<int> depth;
pair<int, int> depth_memo[100000];
pair<int, int> max_depth(int u, int p){
    if(depth_memo[u].first != -1) return depth_memo[u];
    pair<int, int> res(0, u);
    for(int v : G[u]) if(v != p) {
        pair<int, int> pt = max_depth(v, u);
        if(res.first < pt.first + 1){
            res = make_pair(pt.first + 1, pt.second);
        }
    }
    return depth_memo[u] = res;
}
tuple<int, int, int> dfs_memo[100000];
tuple<int, int, int> dfs(int u, int p){
    if(get<0>(dfs_memo[u]) != -1) return dfs_memo[u];
    vector<pair<int, int>> vp;
    vp.push_back( make_pair(0, u) );
    tuple<int, int, int> res;
    for(int v : G[u]) if(v != p){
        vp.push_back( max_depth(v, u) );
    }
    sort(vp.begin(), vp.end(), greater< pair<int, int> >());
    if(vp.size() >= 2) {
        res = make_tuple(vp[0].first + vp[1].first, vp[0].second, vp[1].second);
    }
    for(int v : G[u]) if(v != p) {
        res = max(res, dfs(v, u));
    }
    return dfs_memo[u] = res;
}

int main(){
    int N;
    cin >> N;
    G.resize(N);
    REP(i, N) depth_memo[i] = make_pair(-1, -1);
    REP(i, N) dfs_memo[i] = make_tuple(-1, -1, -1);
    REP(i, N - 1){
        int a, b;
        cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    // printf("max_depth = %d %d\n", max_depth(0, -1).first, max_depth(0, -1).second);
    tuple<int, int, int> res = dfs(0, -1);
    printf("%d %d\n", get<1>(res) + 1, get<2>(res) + 1);
    return 0;
}

