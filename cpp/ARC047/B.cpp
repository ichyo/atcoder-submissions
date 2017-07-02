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

double dist(double dx, double dy) {
    return abs(dx) + abs(dy);
}
int dist(int dx, int dy) {
    return abs(dx) + abs(dy);
}
int main(){
    iostream_init();
    int N;
    cin >> N;
    vector<int> X(N);
    vector<int> Y(N);
    REP(i, N) cin >> X[i] >> Y[i];
    double len = 1e9;
    complex<double> p = {0, 0};
    REP(_, 200) {
        int max_i = 0;
        for(int i = 0; i < N; i++) {
            double px = p.real();
            double py = p.imag();
            double d = dist(X[i] - px, Y[i] - py);
            double cur = dist(X[max_i] - px, Y[max_i] - py);
            if(d > cur) {
                max_i = i;
            }
        }
        auto dif = (complex<double>(X[max_i], Y[max_i]) - p);
        dif /= abs(dif);
        p += dif * len;
        len *= 0.9;
    }
    int answer_x = -1e9 - 1;
    int answer_y = -1e9 - 1;
    const int L = 50;
    for(int dx = -L; dx <= L; dx++) {
        for(int dy = -L; dy <= L; dy++) {
            int x = p.real() + dx;
            int y = p.imag() + dy;
            bool valid = true;
            int d = dist(X[0] - x, Y[0] - y);
            for(int i = 0; i < N; i++) {
                if(dist(X[i] - x, Y[i] - y) != d) {
                    valid = false;
                    break;
                }
            }
            if(valid) {
                answer_x = x;
                answer_y = y;
                goto ANS;
            }
        }
    }
ANS:
    assert(answer_x >= -1e9);
    cout << answer_x << " " << answer_y << endl;
    return 0;
}

