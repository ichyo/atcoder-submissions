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

LL simulate(int b, int A, int B, const vector<int>& X) {
    // [-inf, b) [b, inf)
    LL ans = 0;
    int cur1 = A;
    int cur2 = B;
    REP(i, X.size()) {
        if(X[i] < b) {
            ans += abs(cur1 - X[i]);
            cur1 = X[i];
        } else {
            ans += abs(cur2 - X[i]);
            cur2 = X[i];
        }
    }
    return ans;
}

double find_min(double a, double b, function<double(double)> f) {
    REP(_, 86) {
        double c = (a * 2 + b) / 3;
        double d = (a + b * 2) / 3;
        if(f(c) < f(d)) { // '>': maximum, '<': minimum
            b = d;
        } else {
            a = c;
        }
    }
    return (a + b) / 2;
}

int main(){
    iostream_init();
    int N, Q, A, B;
    cin >> N >> Q >> A >> B;
    vector<int> X(Q);
    REP(i, Q) cin >> X[i];
    function<double(double)> f = [&](double x) {
        int b = x;
        LL t1 = simulate(b, A, B, X);
        LL t2 = simulate(b, B, A, X);
        return min(t1, t2);
    };
    double fx = find_min(0, N, f);
    LL ans = LLONG_MAX;
    for(int b = fx-10; b <= fx+10; b++) {
        ans = min(ans, simulate(b, A, B, X));
        ans = min(ans, simulate(b, B, A, X));
    }
    cout << ans << endl;
    return 0;
}

