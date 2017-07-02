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

int main(){
    iostream_init();

    int N, Q, A, B;
    cin >> N >> Q >> A >> B;
    vector<int> X(Q+2);
    REP(i, Q) cin >> X[i+2];
    X[0] = A; X[1] = B;
    Q += 2;

    const int BEAM = 80;
    typedef pair<LL, int> P;

    priority_queue<P, vector<P>, greater<P>> que;
    que.push(make_pair(0, 0));

    for(int i = 2; i < Q; i++) {
        // cerr << "beam " << i << " " << que.size() << endl;
        priority_queue<P, vector<P>, greater<P>> nque;
        set<int> used;
        map<int, int> dist;
        REP(_, BEAM) {
            if(que.empty()) {
                break;
            }
            auto state = que.top(); que.pop();
            const LL cost = state.first;
            const int idx1 = state.second;
            if(used.count(idx1)) { continue; }
            used.insert(idx1);
            const int idx2 = i-1;
            // cerr << cost << " " << idx1 << " " << idx2 << endl;
            {
                const LL ncost = cost + abs(X[i] - X[idx1]);
                const int nidx = idx2;
                if(!dist.count(nidx) || dist[nidx] > ncost) {
                    dist[nidx] = ncost;
                    nque.push(P(ncost, nidx));
                }
            }
            {
                const LL ncost = cost + abs(X[i] - X[idx2]);
                const int nidx = idx1;
                if(!dist.count(nidx) || dist[nidx] > ncost) {
                    dist[nidx] = ncost;
                    nque.push(P(ncost, nidx));
                }
            }
        }
        que.swap(nque);
    }

    cout << que.top().first << endl;

    return 0;
}

