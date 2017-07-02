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

int main(){
    iostream_init();
    int N;
    cin >> N;
    vector<int> A(N);
    REP(i, N) cin >> A[i];
    // sort(A.begin(), A.end());
    // vector<int> B = A;
    // B.erase(unique(B.begin(), B.end()), B.end());
    map<int, int> C;
    for(int x : A) C[x] ++;

    int ans = C.size();

    int sum = 0;
    for(auto p : C) {
        sum += p.second - 1;
    }

    if(sum % 2 == 1) ans--;

    cout << ans << endl;


    return 0;
}

