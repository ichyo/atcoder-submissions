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
LL calc(const vector<LL>& diff, LL D) {
    LL ans = 0;
    for(int i = 0; i < diff.size(); i++) {
        ans += abs(diff[i] + D);
    }
    return ans;
}
int N;
vector<LL> L;
vector<LL> R;

LL solve(LL first) {
    vector<LL> diff(N);

    diff[0] += first;
    R[0] += first;
    L[0] += first;

    for(int i = 1; i < N; i++) {
        if(R[i-1] < L[i]) {
            diff[i] = R[i-1] - L[i];
            R[i] += diff[i];
            L[i] += diff[i];
        } else if(L[i-1] > R[i]) {
            diff[i] = L[i-1] - R[i];
            R[i] += diff[i];
            L[i] += diff[i];
        }
    }

    auto f = [&](double x) -> double {
        int D = (int)x;
        return calc(diff, x);
    };

    double d = find_min(-2e9, 2e9, f);

    LL ans = LLONG_MAX;
    for(int i = -20; i <= 20; i++) {
        ans = min(ans, calc(diff, (LL)d + i));
    }

    return ans;
}
int main(){
    iostream_init();
    while(cin >> N) {
        L.assign(N, 0);
        R.assign(N, 0);
        REP(i, N){
            cin >> L[i] >> R[i];
        }

        auto f = [&](double x) -> double {
            int D = (int)x;
            double res = solve(D);
            return res;
        };
        double d = find_min(-2e9, 2e9, f);
        LL ans = LLONG_MAX;
        for(int i = -20; i <= 20; i++) {
            ans = min(ans, solve((LL)d + i));
        }

        cout << ans << endl;
    }

    return 0;
}

