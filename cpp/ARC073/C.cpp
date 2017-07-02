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
    vector<pair<LL, LL>> v;
    REP(i, N) {
        LL x, y;
        cin >> x >> y;
        if(x > y) swap(x, y);
        v.push_back(make_pair(x, y));
    }
    sort(v.begin(), v.end());

    vector<LL> a, b;
    REP(i, v.size()) {
        a.push_back(v[i].first);
        b.push_back(v[i].second);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    LL F1 = a.front();
    LL F2 = a.back();
    LL S1 = b.front();
    LL S2 = b.back();
    LL ans = (S2 - S1) * (F2 - F1);

    multiset<LL> s;
    REP(i, N) s.insert(v[i].first);
    for(int i = 0; i <= N; i++) {
        LL min_a = (*s.begin());
        LL max_a = (*(--s.end()));
        // cerr << max_a << " - " << min_a << endl;
        LL sub = (S2 - F1) * (max_a - min_a);
        if(ans > sub) {
            ans = sub;
        }
        if(i < N) {
            s.erase(s.find(v[i].first));
            s.insert(v[i].second);
        }
    }

    cout << ans << endl;

    return 0;
}

