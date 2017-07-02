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
        int y = x % MOD;
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
        val = (unsigned int)((unsigned long long)val * rhs.val % MOD);
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
        if(b&1) w = w * a;
        return w;
    }
}
// }}}
typedef ModInt<1000000007> mint;
int N, C;
mint xsum[500][500];
mint memo[500][500];
bool used[500][500];
mint dfs(int k, int c) {
    if(k == N) { return 1; }
    if(used[k][c]) return memo[k][c];
    mint res = 0;
    if(k == N-1) {
        res = xsum[k][c] * dfs(k+1, 0);
    } else {
        for(int i = 0; i <= c; i++) {
            res += xsum[k][i] * dfs(k+1, c-i);
        }
    }
    memo[k][c] = res;
    used[k][c] = true;
    return res;
}
int main(){
    iostream_init();
    cin >> N >> C;
    vector<int> A(N), B(N);
    REP(i, N) cin >> A[i];
    REP(i, N) cin >> B[i];
    mint powall[501][501] = {};
    for(int i = 1; i <= 500; i++) {
        powall[i][0] = 1;
        for(int j = 0; j < 500; j++) {
            powall[i][j+1] = powall[i][j] * i;
        }
    }
    REP(i, N) {
        for(int j = 0; j <= C; j++) {
            xsum[i][j] = 0;
            for(int x = A[i]; x <= B[i]; x++) {
                xsum[i][j] += powall[x][j];
            }
        }
    }
    memset(used, 0, sizeof(used));
    mint ans = dfs(0, C);
    cout << ans.val << endl;
    return 0;
}

