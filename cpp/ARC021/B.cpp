#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> B(N);
    REP(i, N) cin >> B[i];
    int A = 0;
    bool ng = false;
    for(int b = 0; b < 31; b++){
        ZERO:
        {
            int cur = 0;
            REP(i, N - 1) {
                cur ^= B[i] >> b & 1;
            }
            if((cur ^ 0) == (B[N - 1] >> b & 1)){
                goto NEXT;
            }
        }
        ONE:
        {
            int cur = 1;
            REP(i, N - 1) {
                cur ^= B[i] >> b & 1;
            }
            if((cur ^ 1) == (B[N - 1] >> b & 1)){
                A = A | (1 << b);
                goto NEXT;
            }
        }
        NG:
        cout << -1 << endl;
        return 0;
        NEXT:;
    }
    vector<int> ans;
    ans.push_back(A);
    REP(i, N - 1) ans.push_back(ans.back() ^ B[i]);
    assert(ans.front() ^ ans.back() == B[N - 1]);
    REP(i, N) cout << ans[i] << endl;
    return 0;
}

