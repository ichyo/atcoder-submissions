#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;
typedef vector<int> Node;
typedef vector<Node> Graph;

int scc(const Graph& G, const Graph& RG, vector<int>& cmp) {
    int n = G.size();
    int K = 0; // the number of components

    cmp.assign(n, -1); // cmp[v] := component id of vertex v (0, 1, ..., K-1)
    vector<bool> used(n);
    vector<int> order;

    // ordinary dfs
    function<void(int)> dfs = [&](int u) {
        used[u] = true;
        for(int w : G[u]) if(!used[w]) {
            dfs(w);
        }
        order.push_back(u);
    };
    for(int u = 0; u < n; u++) if(!used[u]) {
        dfs(u);
    }
    reverse(order.begin(), order.end());

    // reverse dfs
    function<void(int)> rdfs = [&](int u) {
        cmp[u] = K;
        for(int w : RG[u]) if(cmp[w] == -1) {
            rdfs(w);
        }
    };
    for(int u : order) if(cmp[u] == -1) {
        rdfs(u);
        K++;
    }

    return K;
}


int main(){
    int n, m, K;
    while(cin >> n >> m >> K) {
        K++;

        char label[333];
        REP(i, n) cin >> label[i];

        Graph G(n), RG(n);
        REP(i, m) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            G[a].push_back(b);
            RG[b].push_back(a);
        }


        vector<int> cmp;
        int CSIZE = scc(G, RG, cmp);
        map<int, vector<int>> mp;
        REP(i, n) mp[ cmp[i] ].push_back(i);

        assert(mp.size() == CSIZE);

        bool D[303][303] = {};
        REP(i, n) for(int j : G[i]) {
            int u = cmp[i];
            int v = cmp[j];
            if(u != v) D[u][v] = true;
        }

        string dp[303][303];
        for(int i = 0; i < CSIZE; i++) {
            assert(mp.count(i));
            string s;
            for(int idx : mp[i]) s += label[idx];

            string from[303];
            for(int j = 0; j < i; j++) if(D[j][i]) {
                for(int k = 0; k < K; k++) {
                    if(dp[j][k].size() == k && (from[k].size() != k || dp[j][k] < from[k])) {
                        from[k] = dp[j][k];
                    }
                }
            }

            REP(k, K) dp[i][k] = from[k];

            sort(s.begin(), s.end());
            for(int len = 1; len <= s.size(); len++) {
                string add = s.substr(0, len);
                for(int k = 0; k + len < K; k++) {
                    if(from[k].size() == k && (dp[i][k+len].size() != k+len || from[k]+add < dp[i][k+len])) {
                        dp[i][k+len] = from[k]+add;
                    }
                }
            }
        }

        string ans(K-1, '~');
        REP(i, n) if(dp[i][K-1].size() == K-1) ans = min(ans, dp[i][K-1]);
        if(ans[0] == '~') {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}

