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

typedef pair<int, int> Query;
//set<Query> queries;
const int MAX_M = 1e5 + 10;
set<int> queries[MAX_M];
map<int, int> result[MAX_M];
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

    // --- optional ---
    int size() const { return sums.size(); }
    LL operator [](int idx) const { return sums[idx]; }
};
int main(){
    iostream_init();

    int N, M;
    while(cin >> N >> M) {
        REP(i, MAX_M) result[i].clear();
        REP(i, MAX_M) queries[i].clear();

        vector<pair<int, int>> ps(N);
        REP(i, N) cin >> ps[i].first >> ps[i].second;
        sort(ps.begin(), ps.end());

        auto set = [&](int x1, int x2, int y1, int y2) {
            // queries.insert(Query(x2, y2));
            // queries.insert(Query(x1-1, y2));
            // queries.insert(Query(x2, y1-1));
            // queries.insert(Query(x1-1, y1-1));
             queries[x2].insert(y2);
             queries[x1-1].insert(y2);
             queries[x2].insert(y1-1);
             queries[x1-1].insert(y1-1);
        };
        auto get = [&](int x1, int x2, int y1, int y2) {
            int res = 0;
            res += result[x2][y2];
            res -= result[x1-1][y2];
            res -= result[x2][y1-1];
            res += result[x1-1][y1-1];
            return res;
        };

        for(int d = 1; d <= M; d++) {
            for(int x = d; x <= M; x += d) {
                set(max(x-d+1, 1), x, x, M);
            }
        }

        int idx = 0;
        int qi = 0;
        BIT bit(M + 1);
        for(int x = 0; x <= M; x++) {
            while(idx < ps.size() && ps[idx].first == x) {
                bit.add(ps[idx].second, 1);
                idx++;
            }

            for(auto y : queries[x]) {
                result[x][y] = (int)bit.get(y);
            }
        }

        for(int d = 1; d <= M; d++) {
            int ans = 0;
            for(int x = d; x <= M; x += d) {
                int g = get(max(1, x-d+1), x, x, M);
                // error(d, x-d+1, x, x, M, g);
                ans += g;
            }
            cout << ans << endl;
        }
        // break;
    }

    return 0;
}

