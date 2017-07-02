#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> A(N);
    REP(i, N) cin >> A[i];
    int ans = INT_MAX;
    for(int s = 0; s < (1 << N); s++) {
        int a = 0, b = 0;
        REP(i, N) {
            if(s >> i & 1) a += A[i];
            else b += A[i];
        }
        ans = min(ans, max(a, b));
    }
    cout << ans << endl;
    return 0;
}

