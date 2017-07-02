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

// ModInt (ref. anta) {{{
template<int MOD>
struct ModInt{
    static const int Mod = MOD;
    unsigned val;
    ModInt():val(0){}
    ModInt(unsigned x):val(x%MOD){}
    ModInt(signed x) {
        int y = x % MOD;
        if(y < 0) y += MOD;
        val = y;
    }
    ModInt(signed long long x) {
        int y = (int)(x % MOD);
        if(y < 0) y += MOD;
        val = y;
    }

    ModInt &operator+=(ModInt rhs) {
        val += rhs.val;
        if(val >= MOD) val -= MOD;
        return *this;
    }
    ModInt &operator-=(ModInt rhs) {
        val += MOD - rhs.val;
        if(val >= MOD) val -= MOD;
        return *this;
    }
    ModInt &operator*=(ModInt rhs) {
        val = (unsigned)((unsigned long long)val * rhs.val % MOD);
        return *this;
    }
    ModInt &operator/=(ModInt rhs) {
        return *this *= rhs.inv();
    }

    ModInt inv() const {
        signed a = val, b = MOD, u = 1, v = 0;
        while(b) {
            signed t = a / b;
            a -= t * b; std::swap(a, b);
            u -= t * v; std::swap(u, v);
        }
        if(u < 0) u += MOD;
        ModInt res;
        res.val = u;
        return res;
    }

    ModInt operator+(ModInt rhs) const {
        return ModInt(*this) += rhs;
    }
    ModInt operator-(ModInt rhs) const {
        return ModInt(*this) -= rhs;
    }
    ModInt operator*(ModInt rhs) const {
        return ModInt(*this) *= rhs;
    }
    ModInt operator/(ModInt rhs) const {
        return ModInt(*this) /= rhs;
    }

    // compare
    bool operator==(ModInt rhs) const {
        return val == rhs.val;
    }
    bool operator!=(ModInt rhs) const {
        return val != rhs.val;
    }
    bool operator< (ModInt rhs) const {
        return val <  rhs.val;
    }
    bool operator<=(ModInt rhs) const {
        return val <= rhs.val;
    }
    bool operator> (ModInt rhs) const {
        return val >  rhs.val;
    }
    bool operator>=(ModInt rhs) const {
        return val >= rhs.val;
    }
};
template<int MOD>
ostream& operator << (ostream& os, const ModInt<MOD> m) {
    return os << m.val;
}
template<int MOD, typename T>
ModInt<MOD> pow(ModInt<MOD> a, T b) {
    if(b == 0) {
        return 1;
    } else {
        auto w = pow(a*a, b/2);
        if(b&1) w *= a;
        return w;
    }
}
// }}}
typedef ModInt<1000000007> mint;

const int MAX_N = 1001;
mint memo[MAX_N * 10];
mint fact(int N) {
    if(N == 0) { return mint(1); }
    if(memo[N].val != 0xffffffff) {
        return memo[N];
    }
    return memo[N] = mint(N) * fact(N-1);
}
mint slow(int N, int A, int B, int C, int D) {
    mint dp[MAX_N] = {};
    dp[N] = 1;

    for(int j = A; j <= B; j++) {
        mint ndp[MAX_N] = {};
        REP(i, N+1) ndp[i] = dp[i];

        for(int i = j; i <= N; i++) {
            if(dp[i].val == 0) continue;
            for(int k = C; k <= D; k++) {
                const int ni = i - j * k;
                if(ni < 0) break;
                auto c = fact(i) / fact(ni) / pow(fact(j), k) / fact(k);
                // error(ni, i, dp[i], c);
                ndp[ni] += dp[i] * c;
            }
        }

        REP(i, N+1) dp[i] = ndp[i];
    }
    return dp[0];
}
int main(){
    iostream_init();
    memset(memo, -1, sizeof(memo));

    int N, A, B, C, D;
    cin >> N >> A >> B >> C >> D;

    cout << slow(N, A, B, C, D) << endl;

    return 0;
}

