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
mint fast(int N, int K) {
    Comb c(10000);
    mint res = c.nCr(N-1, K-1) * pow(mint(2), max(N-K-1, 0));
    for(int a = 1; a <= K-1-1; a++) {
        res += c.nCr(N-1, a) * c.nCr(N-1-a, K-1-a) * pow(mint(2), max(N-K-1, 0));
    }
    return res;
}

deque<int> q;
vector<int> r;
set<vector<int>> ans;
void dfs2(int N, int K) {
    if(r.size() == K && r[K-1] != 1) {
    } else if(q.empty()) {
        ans.insert(r);
    } else {
        int x = q.front();
        int y = q.back();
        q.pop_front();
        r.push_back(x);
        dfs2(N, K);
        r.pop_back();
        q.push_front(x);

        q.pop_back();
        r.push_back(y);
        dfs2(N, K);
        r.pop_back();
        q.push_back(y);
    }
}
void dfs1(int idx, int N, int K) {
    if(idx == N+1) {
        dfs2(N, K);
    } else {
        q.push_back(idx);
        dfs1(idx+1, N, K);
        q.pop_back();

        q.push_front(idx);
        dfs1(idx+1, N, K);
        q.pop_front();
    }
}
mint slow(int N, int K) {
    ans.clear();
    assert(q.empty());
    assert(r.empty());
    dfs1(1, N, K);
    return mint((int)ans.size());
}
int main(){
    iostream_init();
    for(int N = 1; N <= 5; N++) {
        for(int K = 1; K <= N; K++) {
            auto a = fast(N, K);
            auto b = slow(N, K);
            if(a != b) {
                error(N, K, a, b);
                assert(false);
            }
        }
    }
    // // wrong
    //
    // int N, K;
    // cin >> N >> K;
    // cout << fast(N, K) << endl;
    return 0;
}

