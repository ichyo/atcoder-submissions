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

class Knapsack {
    typedef long long LL;
    struct item { 
        LL v, w; 
    };

    LL W;
    vector<item> items;
    LL lv;

    LL solve_rec(size_t k, LL v, LL w) {
        if (w + items[k].w > W) return solve_rec(k+1, v, w);
        LL cv = v, cw = w;
        for (size_t i = k; i < items.size(); ++i) {
            if (cw + items[i].w <= W) {
                cw += items[i].w;
                cv += items[i].v;
            }
        }
        if (lv < cv) lv = cv;
        double fv = v, fw = w;
        for (size_t i = k; i < items.size(); ++i) {
            if (fw + items[i].w <= W) {
                fw += items[i].w;
                fv += items[i].v;
            } else {
                fv += items[i].v * (W - fw) / items[i].w;
                break;
            }
        }
        if (fv - lv < 1 || fv < lv) return lv;
        solve_rec(k+1, v+items[k].v, w+items[k].w);
        return solve_rec(k+1, v, w);
    }

    public:
    // 価値v, 重みwのアイテムを追加
    void add_item(LL v, LL w) {
        items.push_back({v, w});
    }

    // 重みの合計がW以下になるようにアイテムを選んだときの価値の和の最大値を返す．
    LL solve(LL W_) {
        if(items.empty()) return 0;
        W = W_;
        sort(items.begin(), items.end(), [](const item &a, const item &b) { 
                return a.v * b.w > a.w * b.v;
                });
        lv = 0;
        return solve_rec(0, 0, 0);
    };
};

int main(){
    iostream_init();
    int N;
    LL T;
    cin >> N;
    cin >> T;
    LL ans = 0;
    LL last_x = 0;
    REP(i, N) {
        LL x;
        cin >> x;
        LL y = x - last_x;
        last_x = x;
        if(i != 0) {
            ans += min(y, T);
        }
    }
    ans += T;
    cout << ans << endl;

    return 0;
}

