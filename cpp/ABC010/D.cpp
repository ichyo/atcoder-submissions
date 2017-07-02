#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

const int INF = 1000000000;
struct Dinic{
    struct Edge{
        int dst, cap, rev;
        Edge(){}
        Edge(int d, int c, int r) :
            dst(d), cap(c), rev(r) {}
    };
    typedef vector<Edge> Node;
    typedef vector<Node> Graph;

    Graph G;
    vector<int> level;
    vector<int> iter;

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

    Dinic(int N) : G(N), level(N), iter(N) {}

    void add_edge(int src, int dst, int cap){
        G[src].push_back(Edge(dst, cap, G[dst].size()));
        G[dst].push_back(Edge(src, 0, G[src].size() - 1));
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
    int N, G, E;
    cin >> N >> G >> E;
    Dinic solver(N + 1);
    REP(i, G) {
        int t;
        cin >> t;
        solver.add_edge(t, N, 1);
    }
    REP(i, E) {
        int a, b;
        cin >> a >> b;
        solver.add_edge(a, b, 1);
        solver.add_edge(b, a, 1);
    }
    cout << solver.max_flow(0, N) << endl;
    return 0;
}

