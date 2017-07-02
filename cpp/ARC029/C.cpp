#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
typedef pair<int, int> P;

int main(){
    int N, M;
    while(cin >> N >> M) {
        vector<int> c(N);
        REP(i, N) cin >> c[i];
        vector<vector<P>> G(N);
        REP(i, M) {
            int a, b, r;
            cin >> a >> b >> r;
            a--; b--;
            G[a].push_back(P(r, b));
            G[b].push_back(P(r, a));
        }
        priority_queue<P, vector<P>, greater<P>> que;
        long long ans = 0;
        vector<bool> used(N);
        REP(i, N) que.push(P(c[i], i));
        while(!que.empty()){
            P p = que.top(); que.pop();
            int u = p.second, c = p.first;
            if(used[u]) continue;
            used[u] = true;
            ans += c;
            for(P p : G[u]) {
                if(!used[p.second]) {
                    que.push(p);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}

