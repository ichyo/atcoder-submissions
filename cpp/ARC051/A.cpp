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

typedef complex<double> P;
const double EPS = 1e-8;
int sign(double x){ return (x > EPS) - (x < -EPS); }
int comp(double x, double y) { return sign(x - y); }
int main(){
    iostream_init();
    while(true) {
        double r;
        double tmp1, tmp2;
        cin >> tmp1 >> tmp2 >> r;
        P p(tmp1, tmp2);
        double x[2];
        double y[2];
        cin >> x[0] >> y[0] >> x[1] >> y[1];

        if(cin.eof()) break;

        auto check1 = [&]{
            REP(i, 4) {
                P q(x[i % 2], y[i / 2]);
                if(comp(abs(q - p), r) > 0) {
                    return false;
                }
            }
            return true;
        };
        auto check2 = [&]{
            double a = p.real();
            double b = p.imag();
            double x1 = x[0] + r;
            double x2 = x[1] - r;
            double y1 = y[0] + r;
            double y2 = y[1] - r;
            if(!(comp(x1, a) <= 0 && comp(a, x2) <= 0)) {
                return false;
            }
            if(!(comp(y1, b) <= 0 && comp(b, y2) <= 0)) {
                return false;
            }
            return true;
        };

        cout << (check2() ? "NO" : "YES") << endl;
        cout << (check1() ? "NO" : "YES") << endl;
    }
    return 0;
}

