#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;
const LL INF = 1e16;
struct Edge{
    int dst;
    LL cap;
    int rev;
};
const double EPS = 1e-8;
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

    int dfs(int v, int t, LL f){
        if(v == t) return f;
        for(int& i = iter[v]; i < G[v].size(); i++){
            Edge& e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.dst]){
                LL d = dfs(e.dst, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.dst][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    void add_edge(int src, int dst, LL cap){
        G[src].push_back({dst, cap, (int)G[dst].size()});
        G[dst].push_back({src, 0, (int)G[src].size() - 1});
    }

    LL max_flow(int src, int dst){
        LL flow = 0;
        while(true){
            bfs(src);
            if(level[dst] < 0) break;
            iter.assign(G.size(), 0);
            while(true){
                LL f = dfs(src, dst, INF);
                if(f <= 0) break;
                flow += f;
            }
        }
        return flow;
    }
};



int M;
int N;
vector<int> T; // money
vector<int> S; // target
vector<int> A[100]; // N

int main(){
    while(cin >> N >> M) {
        const LL BASE = 100000;
        S.resize(N);
        T.resize(M);
        REP(i, N) cin >> S[i];

        REP(i, N) S[i] *= BASE;

        REP(i, M) cin >> T[i];
        REP(i, N) {
            int K;
            cin >> K;
            A[i].resize(K);
            REP(j, K) cin >> A[i][j];
            REP(j, K) A[i][j]--;
        }

        const int SUM = accumulate(S.begin(), S.end(), 0);

        const int SRC = N + M;
        const int DST = SRC + 1;

        LL lb = 0, ub = 2e5 * BASE;
        while(ub - lb > 1) {
            double x = (lb + ub) / 2;
            Dinic dinic(DST + 1);
            REP(i, M) {
                dinic.add_edge(SRC, i, x * T[i]);
            }
            REP(i, N) {
                dinic.add_edge(i + M, DST, S[i]);
            }
            REP(j, N) for(int i : A[j]) {
                int k = j + M;
                dinic.add_edge(i, k, INF);
            }
            LL val = SUM - dinic.max_flow(SRC, DST);
            if(val > 1) {
                lb = x;
            } else {
                ub = x;
            }
        }
        printf("%.12f\n", 1.0 * ub / BASE);
    }
    return 0;
}

