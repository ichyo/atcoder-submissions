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

vector<LL> calc(int N, const vector<int>& a){
    BIT bit(N + 1);
    LL sum = 0;
    vector<LL> res;
    res.push_back(0);
    for(int x : a) {
        sum += bit.get(N) - bit.get(x);
        res.push_back(sum);
        bit.add(x, 1);
    }
    return res;
}

int main(){
    int N;
    while(cin >> N) {
        if(N <= 3) {
            cout << 0 << endl;
            continue;
        }
        int maxi = -1;
        vector<int> B(N);
        REP(i, N) cin >> B[i];
        REP(i, N) if(B[i] == N) maxi = i;
        assert(maxi != -1);
        vector<int> a;
        vector<int> b;
        REP(i, N) if(i != maxi) a.push_back(B[i]);
        for(int i = N - 1; i >= 0; i--) {
            if(i != maxi) b.push_back(B[i]);
        }
        auto sa = calc(N, a);
        auto sb = calc(N, b);
        LL ans = LLONG_MAX;
        for(int i = 0; i < N; i++) {
            LL j = N - 1 - i;
            //cout << i << " " << j << endl;
            LL cost = abs(i - maxi) + sa[i] + sb[j];
            ans = min(ans, cost);
        }
        cout << ans << endl;
    }
    return 0;
}

