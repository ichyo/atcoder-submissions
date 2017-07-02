#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

int main(){
    int N = 100;
    int M = 100;
    cout << N << " " << M << endl;
    REP(i, N) {
        int s = rand() % 100 + 1;
        cout << s << " ";
    }
    cout << endl;
    REP(i, M) {
        int s = rand() % 100 + 1;
        cout << s << " ";
    }
    cout << endl;
    REP(_, N) {
        int K = 10;
        cout << K << " ";
        vector<int> perm(M);
        REP(i, M) perm[i] = i + 1;
        random_shuffle(perm.begin(), perm.end());
        REP(i, K) cout << perm[i] << " ";
        cout << endl;
    }
    return 0;
}

