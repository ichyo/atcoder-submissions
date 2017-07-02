// Template {{{
#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

#ifdef LOCAL
#include "contest.h"
#else
#define dump(x) 
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
int dfs(vector<int>& A, int N, int K) {
    if(A.size() == N) {
        bool ok = false;
        for(int s = 0; s < N; s++) {
            bool all = true;
            for(int i = 0; i < N; i++) {
                if(A[(s+i) % N] != A[(s+N-1-i+N) % N]) {
                    all = false;
                }
            }
            if(all) ok = true;
        }
        if(ok) { return 1; }
        else { return 0; }
    }
    int res = 0;
    for(int x = 1; x <= K; x++) {
        A.push_back(x);
        res += dfs(A, N, K);
        A.pop_back();
    }
    return res;
}
int count(int N, int K) {
    vector<int> A;
    return dfs(A, N, K);
}
int main(){
    iostream_init();
    const int MAX = 7;
    /*
    for(int n = 1; n <= MAX; n++) {
        for(int k = 1; k <= MAX; k++) {
            cout << n << " " << k << " " << count(n, k) << endl;
        }
    }
    */
    for(int k = 1; k <= MAX; k++) {
        for(int n = 1; n <= MAX; n++) {
            cout << n << " " << k << " " << count(n, k) << endl;
        }
    }
    return 0;
}

