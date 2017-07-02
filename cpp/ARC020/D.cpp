#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

inline int calc(int i, int j, vector<int>& D){
    if(i > j) swap(i, j);
    return (D[j] - D[i]);
}
void make_dict(int K, map<vector<int>, int>& time_dict){
    vector<int> perm(K);
    REP(i, K) perm[i] = i;
    do{
        vector<int> time(K - 1);
        for(int i = 0; i + 1 < K; i++){
            int from = perm[i], to = perm[i + 1];
            if(from > to) swap(from, to);
            for(int j = from; j < to; j++){
                time[j] ++;
            }
        }
        time_dict[time]++;
    }while(next_permutation(perm.begin(), perm.end()));
}
int main(){
    int N, M, K;
    cin >> N >> M >> K;
    const int MOD = 1000000007;
    vector<int> D(N);
    REP(i, N - 1) {
        cin >> D[i + 1];
        D[i + 1] += D[i];
    }
    const int B = 0;
    if(N <= B){
        static int dp[1 << B][30][B] = {};
        REP(i, N) dp[1 << i][0][i] = 1;
        for(int s = 0; s < (1 << N); s++){
            for(int k = 0; k < M; k++){
                for(int i = 0; i < N; i++){
                    if(!(s >> i & 1)) continue;
                    for(int j = 0; j < N; j++){
                        if(s >> j & 1) continue;
                        int nk = (k + calc(i, j, D)) % M;
                        int ns = s | (1 << j);
                        dp[ns][nk][j] += dp[s][k][i];
                        dp[ns][nk][j] %= MOD;
                    }
                }
            }
        }
        int ans = 0;
        for(int s = 0; s < (1 << N); s++){
            if(__builtin_popcount(s) != K) continue;
            for(int i = 0; i < N; i++){
                ans = (ans + dp[s][0][i]) % MOD;
            }
        }
        cout << ans << endl;
    }else{
        int n = N;
        int mod = M;
        map<vector<int>, int> time_dict;
        make_dict(K, time_dict);
        cout << "hoge" << endl;
        int ans = 0;
        for(const auto& dict_p : time_dict){
            const vector<int>& time = dict_p.first;
            const int freq = dict_p.second;
            //REP(i, time.size()) cout << time[i] << " ";
            //cout << freq << endl;
            int dp[100][11][31] = {};
            for(int i = 0; i < n; i++){
                dp[i][0][0] = 1;
            }
            for(int from = 0; from < n; from++){
                for(int use = 0; use + 1 < K; use++){
                    for(int k = 0; k < mod; k++){
                        if(dp[from][use][k] == 0) continue;
                        for(int to = from + 1; to < n; to++){
                            int nk = (k + time[use] * calc(from, to, D)) % mod;
                            dp[to][use + 1][nk] += dp[from][use][k];
                            dp[to][use + 1][nk] %= MOD;
                        }
                    }
                }
            }
            for(int end = 0; end < n; end++){
                ans = (ans + (long long)freq * dp[end][K - 1][0] % MOD) % MOD;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

