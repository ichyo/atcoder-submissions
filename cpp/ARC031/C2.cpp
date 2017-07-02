#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

struct BIT{
    vector<LL> sums;
    BIT(int n) : sums(n) {}

    // v[at] += by
    void add(int at, LL by) {
        while(at < sums.size()){
            sums[at] += by;
            at |= at + 1;
        }
    }

    // v[0] + ... + v[at]
    LL get(int at) {
        LL res = 0;
        while(at >= 0) {
            res += sums[at];
            at = (at & (at + 1)) - 1;
        }
        return res;
    }

    // --- optional ---
    int size() const { return sums.size(); }
    LL operator [](int idx) const { return sums[idx]; }
};

int main(){
    int N;
    while(cin >> N) {
        vector<int> A(N);
        REP(i, N) cin >> A[i];
        vector<pair<int, int>> ps(N);
        REP(i, N) ps[i] = make_pair(A[i], i);
        sort(ps.begin(), ps.end());
        BIT bit(N + 1);
        REP(i, N) bit.add(i, 1);
        LL ans = 0;
        REP(i, N - 1) {
            int idx = ps[i].second;
            bit.add(idx, -1);
            LL left = bit.get(idx);
            LL right = (N - i - 1) - left;
            ans += min(left, right);
        }
        cout << ans << endl;
    }
    return 0;
}

