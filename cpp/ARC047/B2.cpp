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

LL dist(LL dx, LL dy) {
    return abs(dx) + abs(dy);
}
int main(){
    iostream_init();
    int N;
    cin >> N;
    vector<LL> X(N);
    vector<LL> Y(N);
    vector<LL> SX(N);
    vector<LL> SY(N);
    REP(i, N) {
        LL x, y;
        cin >> x >> y;
        SX[i] = x;
        SY[i] = y;
        X[i] = x + y;
        Y[i] = x - y;
        // cout << X[i] << " " << Y[i] << endl;
    }
    LL min_x = *min_element(X.begin(), X.end());
    LL max_x = *max_element(X.begin(), X.end());
    LL min_y = *min_element(Y.begin(), Y.end());
    LL max_y = *max_element(Y.begin(), Y.end());
    LL L = max(max_x - min_x, max_y - min_y);
    assert(L % 2 == 0);
    L /= 2;
    LL ans_x = INT_MIN;
    LL ans_y = INT_MIN;
    if(min_x + 2 * L == max_x) {
        ans_x = min_x + L;
    }
    if(min_y + 2 * L == max_y) {
        ans_y = min_y + L;
    }
    if(ans_x != INT_MIN && ans_y != INT_MIN) {
    } else if(ans_x != INT_MIN) {
        set<LL> ys;
        for(int i = 0; i < N; i++) {
            if(abs(X[i] - ans_x) != L) {
                ys.insert(Y[i]);
            }
        }
        LL base = (max_y - min_y) / 2 + min_y;
        if(ys.size() == 2) {
            ans_y = *ys.begin() + L;
            assert(ys.count(ans_y + L));
        } else if(ys.size() == 1) {
            LL c1 = *ys.begin() + L;
            LL c2 = *ys.begin() - L;
            ans_y = abs(c1 - base) < abs(c2 - base) ? c1 : c2;
        } else if(ys.size() == 0) {
            ans_y = base;
        } else {
            assert(false);
        }
    } else if(ans_y != INT_MIN) {
        set<LL> xs;
        for(int i = 0; i < N; i++) {
            if(abs(Y[i] - ans_y) != L) {
                xs.insert(X[i]);
            }
        }
        LL base = (max_x - min_x) / 2 + min_x;
        if(xs.size() == 2) {
            ans_x = *xs.begin() + L;
            assert(xs.count(ans_x + L));
        } else if(xs.size() == 1) {
            LL c1 = *xs.begin() + L;
            LL c2 = *xs.begin() - L;
            ans_x = abs(c1 - base) < abs(c2 - base) ? c1 : c2;
        } else if(xs.size() == 0) {
            ans_x = base;
        } else {
            assert(false);
        }
    } else {
        assert(false);
    }
    LL e = max(abs(X[0] - ans_x), abs(Y[0] - ans_y));
    for(int i = 0; i < N; i++) {
        LL d = max(abs(X[i] - ans_x), abs(Y[i] - ans_y));
        // cout << d << endl;
        while(d != e);
    }

    // cout << ans_x << endl;
    // cout << ans_y << endl;
    LL bx = (ans_x + ans_y) / 2;
    LL by = ans_x - bx;
    LL out_x = 1e9 + 1;
    LL out_y = 1e9 + 1;
    const int LEN = 10;
    for(int dx = -LEN; dx <= LEN; dx++) {
        for(int dy = -LEN; dy <= LEN; dy++) {
            LL x = bx + dx;
            LL y = by + dy;
            if(abs(x) > 1e9) continue;
            if(abs(y) > 1e9) continue;
            bool valid = true;
            LL d = dist(SX[0] - x, SY[0] - y);
            for(int i = 0; i < N; i++) {
                if(dist(SX[i] - x, SY[i] - y) != d) {
                    valid = false;
                    break;
                }
            }
            if(valid) {
                out_x = x;
                out_y = y;
            }
        }
    }
    assert(abs(out_x) <= 1e9);
    assert(abs(out_y) <= 1e9);
    // cout << ans_x << " " << ans_y << endl;
    cout << out_x << " " << out_y << endl;
    return 0;
}

