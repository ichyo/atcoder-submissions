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
template<int MOD>
struct CombM{
    static const int Mod = MOD;
    typedef ModInt<MOD> mint;
    vector<mint> fact;
    vector<mint> factinv;
    CombM(int N) {
        N = min(N, MOD-1);
        fact.resize(N+1);
        factinv.resize(N+1);
        REP(i, N+1) {
            fact[i] = (i == 0 ? 1 : fact[i-1] * i);
        }
        factinv[N] = fact[N].inv();
        for(int i = N; i >= 1; i--) factinv[i-1] = factinv[i] * i;
    }

    mint nCr(int n, int r) {
        assert(n < (int)fact.size());
        if(n >= MOD) return nCr(n%MOD, r%MOD) * nCr(n/MOD, r/MOD); // Lucas' theorem
        return r > n ? 0 : fact[n] * factinv[n-r] * factinv[r];
    }

    mint nHr(int n, int r) {
        return r == 0 ? 1 : nCr(n+r-1, r);
    }
};
typedef CombM<1000000007> Comb;
int main(){
    iostream_init();
    int N;
    cin >> N;
    string s;
    cin >> s;
    int T = s.size();
    mint ans = 0;
    Comb comb(5005);
    for(int b = 0; b <= N-T; b++) {
        int M = N - b;
        if((M - T) % 2 != 0){ continue; }
        int A = T;
        int B = (M - T) / 2;
        ans += comb.nCr(A + B, A) * pow(mint(2), B);
    }
    cout << ans << endl;
    return 0;
}

