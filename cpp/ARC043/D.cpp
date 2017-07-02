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

class range {
    struct Iterator {
        int val, inc;
        int operator*() {return val;}
        bool operator!=(Iterator& rhs) {return val < rhs.val;}
        void operator++() {val += inc;}
    };
    Iterator i, n;
    public:
    range(int e) : i({0, 1}), n({e, 1}) {}
    range(int b, int e) : i({b, 1}), n({e, 1}) {}
    range(int b, int e, int inc) : i({b, inc}), n({e, inc}) {}
    Iterator& begin() {return i;}
    Iterator& end() {return n;}
};

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
    int M;
    cin >> M;
    assert(N <= 10);
    vector<int> P(M);
    REP(i, M) cin >> P[i];
    vector<int> perm(N);
    REP(i, N) perm[i] = i;
    int answer = INT_MIN;
    do{
        int cost = 0;
        REP(j, N) REP(i, j) {
            int x = perm[i];
            int y = perm[j];
            if(x < M && y < M) {
                cost += (j-i) * P[x] * P[y];
            }
        }
        answer = max(answer, cost);
    }while(next_permutation(perm.begin(), perm.end()));
    cout << answer << endl;
    return 0;
}

/* vim:set foldmethod=marker: */

