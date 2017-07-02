// Template {{{
#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

template<typename T1, typename T2>
ostream& operator << (ostream& os, const pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream& os, const vector<T>& v) {
    os << "";
    for(int i = 0; i < v.size(); i++)
        os << v[i] << (i+1<v.size()?" ":"");
    os << "";
    return os;
}

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
inline bool valid(int x, int w) { return 0 <= x && x < w; }

void iostream_init() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
//}}}

typedef pair<int, int> P;
typedef tuple<int, int, int> T; // (time, type, id)
int main(){
    iostream_init();

    int n;
    while(cin >> n) {
        vector<int> a(n);
        vector<int> b(n);
        REP(i, n) cin >> a[i] >> b[i];

        vector<P> ps(n);
        REP(i, n) ps[i] = make_pair(b[i], i);
        sort(ps.begin(), ps.end());

        vector<int> ids(n);
        vector<int> last;
        last.push_back(INT_MIN);
        REP(i, n) {
            int idx = ps[i].second;
            int k = upper_bound(last.begin(), last.end(), a[idx]) - last.begin();
            if(k == last.size()) {
                last.push_back(b[idx]);
                ids[idx] = k;
            } else {
                last[k] = min(last[k], b[idx]);
                ids[idx] = k;
            }
        }
        // cout << "ids: " << ids << endl;
        // cout << "last:" << last << endl;
        int L = last.size();
        vector< vector<int> > id2idx(L);
        REP(i, n) id2idx[ ids[i] ].push_back(i);

        vector<int> max_a(L+1, INT_MIN);
        max_a[L] = INT_MAX;
        for(int id = L-1; id >= 1; id--) {
            for(int idx : id2idx[id]) {
                if(b[idx] <= max_a[id+1]) {
                    max_a[id] = max(max_a[id], a[idx]);
                }
            }
        }
        // cout << "max_a: " << max_a << endl;
        vector<int> ans;
        int last_b = INT_MIN;

        for(int id = 1; id < L; id++) {
            int take = INT_MAX;
            for(int idx : id2idx[id]) if(idx < take) {
                if(last_b <= a[idx] && b[idx] <= max_a[id+1]) {
                    take = idx;
                }
            }
            // cout << "take: " << take << endl;
            assert(take != INT_MAX);
            ans.push_back(take+1);
            last_b = b[take];
        }
        cout << ans.size() << endl;
        cout << ans << endl;
    }


    return 0;
}

/* vim:set foldmethod=marker: */

