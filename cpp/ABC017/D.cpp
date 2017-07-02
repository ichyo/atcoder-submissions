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
    os << "{";
    for(int i = 0; i < v.size(); i++)
        os << v[i] << (i+1<v.size()?", ":"");
    os << "}";
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

static const unsigned MODVAL = 1000000007;
struct mint {
    unsigned val;
    mint():val(0){}
    mint(int      x):val(x%MODVAL) {}
    mint(unsigned x):val(x%MODVAL) {}
    mint(LL       x):val(x%MODVAL) {}
};
mint& operator+=(mint& x, mint y) { return x = x.val+y.val; }
mint& operator-=(mint& x, mint y) { return x = x.val-y.val+MODVAL; }
mint& operator*=(mint& x, mint y) { return x = LL(x.val)*y.val; }
mint operator+(mint x, mint y) { return x+=y; }
mint operator-(mint x, mint y) { return x-=y; }
mint operator*(mint x, mint y) { return x*=y; }
int main(){
    iostream_init();

    int N, M;
    while(cin >> N >> M) {
        vector<int> f(N);
        REP(i, N) cin >> f[i];
        vector<mint> sum(N + 2);
        vector<mint> dp(N + 2);
        dp[0] = 1;
        sum[0+1] = sum[0] + dp[0];
        vector<int> last(M + 1, -1);
        int B = -1;
        for(int i = 0; i < N; i++) {
            B = max(B, last[ f[i] ]);
            last[ f[i] ] = i;
            // [B+1, i-1]
            dp[i+1] += sum[i+1] - sum[B+1];
            sum[i+2] = sum[i+1] + dp[i+1];
        }
        cout << dp[N].val << endl;
    }
    return 0;
}

/* vim:set foldmethod=marker: */

