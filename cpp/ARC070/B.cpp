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
const int MAX_K = 5050;
vector<bool> slow(int N, int K, vector<int> A) {
    vector<bool> answer(N);
    REP(i, N) {
        bool dp[MAX_K] = {};
        dp[0] = true;
        REP(x, N) if(x != i) {
            bool ndp[MAX_K] = {};
            REP(y, K+1) {
                ndp[y] = (dp[y] || (y-A[x] >= 0 && dp[y-A[x]]));
            }
            REP(y, K+1) dp[y] = ndp[y];
        }
        REP(y, K) if(dp[y] && K <= y + A[i] && y < K) {
            answer[i] = true;
        }
    }
    return answer;
}

bool ok(vector<int> A, int i, int K) {
    int N = A.size();
    bool dp[MAX_K] = {};
    dp[0] = true;
    REP(x, N) if(x != i) {
        bool ndp[MAX_K] = {};
        REP(y, K+1) {
            ndp[y] = (dp[y] || (y-A[x] >= 0 && dp[y-A[x]]));
        }
        REP(y, K+1) dp[y] = ndp[y];
    }
    REP(y, K) if(dp[y] && K <= y + A[i] && y < K) {
        return true;
    }
    return false;
}

int main(){
    iostream_init();
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    REP(i, N) cin >> A[i];
    vector<int> B;
    REP(i, N) {
        if(A[i] < K) {
            B.push_back(A[i]);
        }
    }
    A = B;
    N = A.size();

    sort(A.begin(), A.end());
    reverse(A.begin(), A.end());

    if(N == 0 || !ok(A, 0, K)) {
        cout << N << endl;
        return 0;
    }

    int b = 0, e = N;
    while(e - b > 1) {
        int m = (b + e) / 2;
        if(ok(A, m, K)) {
            b = m;
        } else {
            e = m;
        }
    }
    cout << N - (b+1) << endl;
    return 0;
}

