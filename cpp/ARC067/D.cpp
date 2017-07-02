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

LL calc(int s, const vector<LL>& A, const vector<vector<LL>>& BS) {
    const int N = BS.size();
    const int M = BS[0].size();

    LL sum = 0;
    REP(i, M) sum += BS[s][i];
    LL ans = sum;

    LL cost = 0;
    vector<LL> B(M);
    REP(i, M) B[i] = BS[s][i];

    for(int i = s+1; i < N; i++) {
        cost += A[i-1];

        REP(j, M) {
            LL x = BS[i][j];
            if(B[j] < x) {
                sum += x - B[j];
                B[j] = x;
            }
        }

        ans = max(ans, sum - cost);
    }

    return ans;
}
int main(){
    iostream_init();
    int N, M;
    cin >> N >> M;

    vector<LL> A(N-1);
    REP(i, N-1) cin >> A[i];

    vector<vector<LL>> BS(N, vector<LL>(M));

    REP(i, N) REP(j, M) cin >> BS[i][j];

    LL ans = LLONG_MIN;

    vector<int> eval(N, INT_MAX);

    REP(j, M) {
        vector<pair<int, int>> ps;
        REP(i, N) {
            ps.push_back(make_pair(-BS[i][j], i));
        }
        sort(ps.begin(), ps.end());
        REP(i, N) {
            eval[ps[i].second] = min(eval[ps[i].second], i);
        }
    }

    vector<pair<LL, int>> ps;
    REP(i, N) {
        ps.push_back(make_pair(eval[i], i));
    }
    sort(ps.begin(), ps.end());

    clock_t start = clock();
    int index = -1;
    REP(i, ps.size()) {
        clock_t end = clock();
        if((end - start) > 1.8 * CLOCKS_PER_SEC) {
            break;
        }
        
        auto c = calc(ps[i].second, A, BS);
        if(ans < c) {
            ans = c;
            index = ps[i].second;
        }
    }
    for(int i = index - 10; i <= index + 10; i++) {
        if(i >= 0 && i < N) {
            ans = max(ans, calc(i, A, BS));
        }
    }
    cout << ans << endl;
    return 0;
}

