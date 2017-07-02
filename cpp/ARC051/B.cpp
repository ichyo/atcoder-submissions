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

int main(){
    iostream_init();
    vector<LL> answer = {0, 1};
    LL a = 0, b = 1;
    REP(_, 41) {
        LL c = a + b;
        answer.push_back(c);
        a = b;
        b = c;
    }
    int K;
    cin >> K;
    cout << answer[K+2] << " " << answer[K+1] << endl;
    return 0;
}

