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

class range {
    struct Iterator {
        int val, inc;
        int operator*() {return val;}
        bool operator!=(Iterator& rhs) {return val < rhs.val;}
        void operator++() {val += inc;}
    };
    Iterator i, n;
    public:
    range(int e) : i({0, 1}), n({e, 1}) {}
    range(int b, int e) : i({b, 1}), n({e, 1}) {}
    range(int b, int e, int inc) : i({b, inc}), n({e, inc}) {}
    Iterator& begin() {return i;}
    Iterator& end() {return n;}
};

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
        val = (unsigned long long)val * rhs.val % MOD;
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

struct CumSum {
    typedef mint Sum;
    vector<Sum> v;

    template<typename T>
    CumSum(const vector<T>& a): v(a.size()+1) {
        for(size_t i = 0; i < a.size(); i++) {
            v[i+1] = v[i] + a[i];
        }
    }

    // [l, r)
    inline Sum get(int l, int r) const {
        return v[r] - v[l] + (l >= r ? v.back() : 0);
    }
};

int main(){
    iostream_init();
    int N;
    cin >> N;
    vector<int> D(N);
    REP(i, N) cin >> D[i];
    sort(D.begin(), D.end());
    vector<mint> ways(N, 1);
    CumSum sum(ways);
    REP(_, 3) {
        vector<mint> nways(N);
        for(int i = 0; i < N; i++) {
            int k = upper_bound(D.begin(), D.end(), D[i] / 2) - D.begin();
            if(k > 0) {
                nways[i] = sum.get(0, k);
            }
        }
        ways.swap(nways);
        sum = CumSum(ways);
    }
    mint ans = 0;
    REP(i, N) ans += ways[i];
    cout << ans.val << endl;
    return 0;
}

/* vim:set foldmethod=marker: */

