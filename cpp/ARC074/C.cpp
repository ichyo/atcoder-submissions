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

int main(){
    iostream_init();
    int N, M;
    while(cin >> N >> M) {
        int l[303], r[303], x[303];
        REP(i, M) cin >> l[i] >> r[i] >> x[i];
        REP(i, M) l[i]--;
        REP(i, M) r[i]--;

        vector<pair<int, int>> segs[303];
        REP(i, M) {
            segs[r[i]].push_back(make_pair(l[i], x[i]));
        }

        static mint dp[303][303][303] = {};
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        REP(i, N) REP(a, i+1) REP(b, i+1) if(dp[i][a][b] != 0) {
            {
                // a
                const int al = i+1;
                const int bl = b;
                const int cl = i;
                const int na = b;
                const int nb = i;

                bool ok = true;
                for(auto p : segs[i]) {
                    const int cnt = (al != 0 && al > p.first) + (bl != 0 && bl > p.first) + (cl != 0 && cl > p.first);
                    if(cnt != p.second){ ok = false; break; }
                }
                if(ok) { dp[i+1][na][nb] += dp[i][a][b]; }
            }
            {
                // b
                const int al = a;
                const int bl = i+1;
                const int cl = i;
                const int na = a;
                const int nb = i;

                bool ok = true;
                for(auto p : segs[i]) {
                    const int cnt = (al != 0 && al > p.first) + (bl != 0 && bl > p.first) + (cl != 0 && cl > p.first);
                    if(cnt != p.second){ ok = false; break; }
                }
                if(ok) { dp[i+1][na][nb] += dp[i][a][b]; }
            }
            {
                // c
                const int al = a;
                const int bl = b;
                const int cl = i+1;
                const int na = a;
                const int nb = b;

                bool ok = true;
                for(auto p : segs[i]) {
                    const int cnt = (al != 0 && al > p.first) + (bl != 0 && bl > p.first) + (cl != 0 && cl > p.first);
                    if(cnt != p.second){ ok = false; break; }
                }
                if(ok) { dp[i+1][na][nb] += dp[i][a][b]; }
            }
        }
        mint ans = 0;
        REP(a, N+1) REP(b, N+1) ans += dp[N][a][b];
        cout << ans << endl;
    }
    return 0;
}

