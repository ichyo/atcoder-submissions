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

typedef complex<double> P;
const double EPS = 1e-8;
struct C{P p;double r;};

struct Edge{
    int dst;
    double cost;
};

typedef vector<Edge> Node;
typedef vector<Node> Graph;

void add_edge(Graph& G, int a, int b, double c) {
    G[a].push_back({b, c});
}

double distance(C c1, C c2) {
    double d = abs(c1.p - c2.p);
    return max(0.0, d - c1.r - c2.r);
}

vector<double> dijkstra(const Graph& G, int s){
    typedef pair<double, int> P;
    priority_queue<P, vector<P>, greater<P>> que;
    vector<double> dist(G.size(), 1e60);
    que.push(P(0.0, s));
    dist[s] = 0.0;
    while(!que.empty()){
        P p = que.top(); que.pop();
        int v = p.second;
        double c = p.first;
        if(c > dist[v]) continue;
        for(auto& e : G[v]){
            if(dist[e.dst] > dist[v] + e.cost){
                dist[e.dst] = dist[v] + e.cost;
                que.push(P(dist[e.dst], e.dst));
            }
        }
    }
    return dist;
}


int main(){
    iostream_init();
    double sx, sy, gx, gy;
    while(cin >> sx >> sy >> gx >> gy) {
        C start, goal;
        start.p = P(sx, sy);
        start.r = 0;
        goal.p = P(gx, gy);
        goal.r = 0;
        int N;
        cin >> N;
        vector<C> circles(N);
        REP(i, N) {
            double x, y, r;
            cin >> x >> y >> r;
            circles[i].p = P(x, y);
            circles[i].r = r;
        }
        circles.push_back(start);
        circles.push_back(goal);

        const int M = circles.size();
        Graph G(M);
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < M; j++) {
                if(i != j) {
                    add_edge(G, i, j, distance(circles[i], circles[j]));
                }
            }
        }
        auto dist = dijkstra(G, M-2);
        cout << dist.back() << endl;
    }
    return 0;
}

