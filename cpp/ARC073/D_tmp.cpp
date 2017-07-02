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

typedef tuple<int, int, int> State;
long long to_long(const State& state) {
    return (((long long)get<1>(state)) << 32) | (get<2>(state));
}
int main(){
    iostream_init();
    int N, Q, A, B;
    cin >> N >> Q >> A >> B;
    vector<int> X(Q + 2);
    X[0] = A; X[1] = B;
    REP(i, Q) cin >> X[i+2];
    Q += 2;
    unordered_map<long long, int> dist;
    priority_queue<State, vector<State>, greater<State>> queue;
    State init(0, 1, 0);
    queue.push(init);
    dist[to_long(init)] = 0;
    LL ans = LLONG_MAX;
    while(!queue.empty()) {
        State state = queue.top(); queue.pop();
        const int cost = get<0>(state);
        const int a = get<1>(state);
        const int b = get<2>(state);
        if(dist[to_long(state)] < cost) {
            continue;
        }
        cerr << a << endl;
        // cerr << cost << " " << a << " " << b << endl;
        if(a == Q-1) {
            ans = cost;
            break;
        }
        {
            State nstate(cost + abs(X[a+1]-X[a]), a+1, b);
            const long long lg = to_long(nstate);
            if(!dist.count(lg) || dist[lg] > get<0>(nstate)) {
                queue.push(nstate);
                dist[lg] = get<0>(nstate);
            }
        }
        {
            State nstate(cost + abs(X[a+1]-X[b]), a+1, a);
            const long long lg = to_long(nstate);
            if(!dist.count(lg) || dist[lg] > get<0>(nstate)) {
                queue.push(nstate);
                dist[lg] = get<0>(nstate);
            }
        }
    }
    cout << ans << endl;
    return 0;
}

