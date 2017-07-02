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

int f(int x, int d) {
    return min(abs(x - d), x);
}

struct BIT{
    vector<LL> sums;
    BIT(int n) : sums(n) {}

    // v[at] += by
    void add(int at, LL by) {
        while(at < sums.size()){
            sums[at] += by;
            at |= at + 1;
        }
    }

    // v[0] + ... + v[at]
    LL get(int at) {
        LL res = 0;
        while(at >= 0) {
            res += sums[at];
            at = (at & (at + 1)) - 1;
        }
        return res;
    }

    // [a, b)
    LL get(int a, int b) {
        return get(b-1) - get(a-1);
    }

    // --- optional ---
    int size() const { return sums.size(); }
    LL operator [](int idx) const { return sums[idx]; }
};

int main(){
    iostream_init();
    int N, D;
    while(cin >> N >> D) {
        vector<int> d(N);
        REP(i, N) cin >> d[i];
        int Q;
        cin >> Q;
        vector<int> q(Q);
        REP(i, Q) cin >> q[i];
        REP(i, Q) q[i]--;

        vector<int> cur(N + 1);
        cur[0] = D;
        for(int i = 0; i < N; i++) {
            cur[i+1] = f(cur[i], d[i]);
        }

        map<int, int> last_index;
        REP(i, N) {
            last_index[d[i]] = i;
        }

        BIT bit(N);
        REP(i, N) bit.add(i, d[i]);

        vector<bool> answer(Q);
        auto ok1 = [&](int i){
            const int li = last_index[1];
            const LL s = bit.get(i+1, li+1);
            return cur[i] > s;
        };
        auto ok2 = [&](int i){
            const int li = last_index[1];
            const LL s = bit.get(i+1, li+1);
            return cur[i] > s;
        };
        REP(i, Q) {
            int idx = q[i];
            if(cur[idx] == 0) {
                answer[i] = false;
            } else if(cur[N] > 0) {
                answer[i] = true;
            } else if(!last_index.count(1)) {
                answer[i] = true;
            } else if(ok1(idx)) {
                answer[i] = true;
            } else {
                // TODO
                answer[i] = false;
            }
        }

        REP(i, Q) {
            cout << (answer[i] ? "YES" : "NO") << endl;
        }
    }
    return 0
}

