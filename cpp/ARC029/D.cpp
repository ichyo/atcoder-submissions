#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int N;
int S[5555];
typedef vector<int> Node;
typedef vector<Node> Graph;
Graph G;

int main(){
    while(cin >> N){
        REP(i, N) cin >> S[i];
        G.assign(N, Node());
        REP(i, N - 1) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            G[a].push_back(b);
        }
        long long sum = 0;
        REP(i, N) sum += S[i];
        typedef pair<int, int> P;
        priority_queue<P, vector<P>, greater<P>> que;
        vector<long long> score(N);
        que.push(P(S[0], 0));
        REP(i, N) {
            P p = que.top(); que.pop();
            score[i + 1] = score[i] + p.first;
            cout << score[i + 1] << " ";
            for(int v : G[p.second]) {
                que.push(P(S[v], v));
            }
        }
        cout << endl;

        int M;
        cin >> M;
        vector<int> T(M);
        REP(i, M) cin >> T[i];
        sort(T.begin(), T.end(), greater<int>());
        vector<long long> score2(M + 1);
        REP(i, M) score2[i + 1] = score2[i] + T[i];

        long long ans = 0;
        REP(i, min(M, N) + 1) {
            cout << score[i] << " " << score2[i] << endl;
            ans = max(ans, sum - score[i] + score2[i]);
        }
        cout << ans << endl;

    }
    return 0;
}

