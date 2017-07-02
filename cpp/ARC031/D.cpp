#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

std::chrono::time_point<std::chrono::system_clock> start;
double answer;
bool used[100]; // T : M
bool taken[100]; // S : N
int cost; // sum T
int have; // sum S
int M;
int N;
vector<int> T; // money
vector<int> S; // target
vector<int> A[100]; // N
void dfs(int B) {
    vector<pair<double, int>> cand;
    for(int i = B; i < N; i++) {
        if(!taken[i]) {
            int ncost = cost;
            int nhave = have + S[i];
            for(int x : A[i]) {
                if(!used[x]) {
                    ncost += T[x];
                }
            }
            double val = 1.0 * nhave / ncost;
            cand.push_back(make_pair(val, i));
        }
    }
    if(cand.empty()) {
        return;
    }

    sort(cand.begin(), cand.end());
    reverse(cand.begin(), cand.end());
    answer = max(answer, cand.front().first);

    int MAX = (B == 0 ? 100 : 6);

    for(int _ = 0; _ < MAX && _ < cand.size(); _++) {
        int ni = cand[_].second;
        bool tmp[100];
        int tmpc = cost;
        REP(i, M) tmp[i] = used[i];

        for(int x : A[ni]) {
            if(!used[x]) {
                used[x] = true;
                cost += T[x];
            }
        }
        taken[ni] = true;
        have += S[ni];

        dfs(ni + 1);

        taken[ni] = false;
        have -= S[ni];
        REP(i, M) used[i] = tmp[i];
        cost = tmpc;
    }
}

int main(){
    while(cin >> N >> M) {
        start = chrono::system_clock::now();
        answer = 0.0;
        S.resize(N);
        T.resize(M);
        REP(i, N) cin >> S[i];
        REP(i, M) cin >> T[i];
        REP(i, N) {
            int K;
            cin >> K;
            A[i].resize(K);
            REP(j, K) cin >> A[i][j];
            REP(j, K) A[i][j]--;
        }

        dfs(0);
        printf("%.12f\n", answer);
    }
    return 0;
}

