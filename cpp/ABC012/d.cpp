#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    int d[500][500] = {};
    const int INF = 1 << 29;
    REP(i, n) REP(j, n) d[i][j] = (i == j ? 0 : INF);
    REP(i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        d[a][b] = d[b][a] = c;
    }
    REP(k, n) REP(i, n) REP(j, n) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    vector<int> v;
    REP(i, n) {
        int max_d = 0;
        REP(j, n) max_d = max(max_d, d[i][j]);
        v.push_back(max_d);
    }
    int ans = *min_element(v.begin(), v.end());
    cout << ans << endl;
    return 0;
}

