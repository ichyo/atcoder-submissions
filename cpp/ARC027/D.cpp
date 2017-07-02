#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
const int MOD = 1000000007;

int main(){
    int N;
    while(cin >> N){
        assert(N <= 500);
        vector<int> h(N);
        REP(i, N) cin >> h[i];
        int D;
        cin >> D;
        while(D--) {
            int s, t;
            cin >> s >> t;
            s--; t--;
            int dp[505] = {};
            dp[s] = 1;
            for(int i = s; i < t; i++) {
                for(int j = i + 1; j <= i + h[i] && j <= t; j++) {
                    dp[j] += dp[i];
                    dp[j] %= MOD;
                }
            }
            cout << dp[t] << endl;
        }
    }
    return 0;
}

