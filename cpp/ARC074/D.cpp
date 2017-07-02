// Template {{{
#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

#ifdef LOCAL
#include "contest.h"
#else
#define error(args...) 
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
const int INF = 1e9;
struct Edge{
    int dst, cap, rev;
};
typedef vector<Edge> Node;
typedef vector<Node> Graph;
struct Dinic{
    Graph G;
    vector<int> level;
    vector<int> iter;
    
    Dinic(int N) : G(N), level(N), iter(N) {}

    void bfs(int s){
        level.assign(G.size(), -1);
        queue<int> que;
        que.push(s);
        level[s] = 0;
        while(!que.empty()){
            int v = que.front(); que.pop();
            for(const auto& e : G[v]){
                if(e.cap > 0 && level[e.dst] < 0){
                    level[e.dst] = level[v] + 1;
                    que.push(e.dst);
                }
            }
        }
    }

    int dfs(int v, int t, int f){
        if(v == t) return f;
        for(int& i = iter[v]; i < G[v].size(); i++){
            Edge& e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.dst]){
                int d = dfs(e.dst, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.dst][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    void add_edge(int src, int dst, int cap){
        G[src].push_back({dst, cap, (int)G[dst].size()});
        G[dst].push_back({src, 0, (int)G[src].size() - 1});
    }

    int max_flow(int src, int dst){
        int flow = 0;
        while(true){
            bfs(src);
            if(level[dst] < 0) break;
            iter.assign(G.size(), 0);
            while(true){
                int f = dfs(src, dst, INF);
                if(f <= 0) break;
                flow += f;
            }
        }
        return flow;
    }
};
int main(){
    iostream_init();
    int H, W;
    while(cin >> H >> W) {
        string grid[100];
        REP(y, H) cin >> grid[y];
        vector<pair<int, int>> ps;
        REP(y, H) REP(x, W) if(grid[y][x] == 'S') ps.push_back(make_pair(x, y));
        REP(y, H) REP(x, W) if(grid[y][x] == 'T') ps.push_back(make_pair(x, y));
        REP(y, H) REP(x, W) if(grid[y][x] == 'o') ps.push_back(make_pair(x, y));

        Dinic dinic(ps.size() + ps.size() + W + H);
        REP(i, ps.size()) {
            int w = ps[i].first + ps.size() + ps.size();
            int h = ps[i].second + W + ps.size() + ps.size();
            dinic.add_edge(i, i + ps.size(), 1);
            dinic.add_edge(i + ps.size(), w, INF);
            dinic.add_edge(w, i, INF);
            dinic.add_edge(i + ps.size(), h, INF);
            dinic.add_edge(h, i, INF);
        }
        int ans = dinic.max_flow(0 + ps.size(), 1);
        if(ps[0].first == ps[1].first) ans = -1;
        if(ps[0].second == ps[1].second) ans = -1;
        cout << ans << endl;
    }
    return 0;
}

