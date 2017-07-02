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
    while(cin >> N) {
        int L = 3*N;
        vector<LL> A(L);
        REP(i, L) cin >> A[i];

        vector<LL> first_sum(L+1, -1);
        vector<LL> second_sum(L+1, -1);
        {
            multiset<LL> s;
            for(int i = 0; i < A.size(); i++) {
                if(s.size() < N) {
                    s.insert(A[i]);
                    if(s.size() == N) {
                        first_sum[i+1] = 0;
                        for(LL x : s) { first_sum[i+1] += x; }
                    }
                } else if(*s.begin() < A[i]) {
                    LL add = A[i] - *s.begin();
                    s.erase(s.begin());
                    s.insert(A[i]);
                    first_sum[i+1] = first_sum[i] + add;
                } else {
                    first_sum[i+1] = first_sum[i];
                }
            }
        }
        {
            multiset<LL> s;
            for(int i = A.size()-1; i >= 0; i--) {
                if(s.size() < N) {
                    s.insert(-A[i]);
                    if(s.size() == N) {
                        second_sum[i] = 0;
                        for(LL x : s) { second_sum[i] += -x; }
                    }
                } else if(-(*s.begin()) > A[i]) {
                    LL add = A[i] - (-*s.begin());
                    s.erase(s.begin());
                    s.insert(-A[i]);
                    second_sum[i] = second_sum[i+1] + add;
                } else {
                    second_sum[i] = second_sum[i+1];
                }
            }
        }
        LL ans = LLONG_MIN;
        for(int i = 0; i < A.size(); i++) {
            if(first_sum[i+1] != -1 && second_sum[i+1] != -1) {
                ans = max(ans, first_sum[i+1] - second_sum[i+1]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}

