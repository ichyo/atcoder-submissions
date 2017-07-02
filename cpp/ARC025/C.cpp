#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

typedef long long LL;
struct Edge{
  int src, dst;
  LL cost;
  Edge(int f, int t, LL c) : src(f), dst(t), cost(c) {}
};

typedef vector<Edge> Node;
typedef vector<Node> Graph;

vector<LL> dijkstra(const Graph& G, int s){
    typedef pair<int, LL> P;
    priority_queue<P, vector<P>, greater<P>> que;
    vector<LL> res(G.size(), LLONG_MAX);
    que.push(P(0, s));
    res[s] = 0;
    while(!que.empty()){
        P p = que.top(); que.pop();
        int v = p.second, c = p.first;
        if(c > res[v]) continue;
        for(auto& e : G[v]){
            if(res[e.dst] > res[v] + e.cost){
                res[e.dst] = res[v] + e.cost;
                que.push(P(res[e.dst], e.dst));
            }
        }
    }
    return res;
}

int main(){
    int N, M, R, T;
    while(cin >> N >> M >> R >> T) {
        Graph G(N);
        REP(i, M) {
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--;
            G[a].push_back(Edge(a, b, c));
            G[b].push_back(Edge(b, a, c));
        }
        long long res = 0;
        REP(s, N) {
            vector<LL> d = dijkstra(G, s);
            swap(d[s], d[d.size() - 1]);
            d.pop_back();
            sort(d.begin(), d.end());
            for(int i = 0; i < d.size(); i++){
                LL D = d[i];
                // D / T < d[j] / R
                // d[j] > D * R / T
                int k = upper_bound(d.begin(), d.end(), D * R / T) - d.begin();
                res += d.size() - k;
                if(k <= i) {
                    res--;
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}

