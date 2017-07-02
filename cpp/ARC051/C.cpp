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
int main(){
    iostream_init();
    int N;
    while(cin >> N) {
        int A, B;
        cin >> A >> B;

        vector<__int128> x(N);
        REP(i, N){
            LL a;
            cin >> a;
            x[i] = a;
        }

        if(A == 1) {
            sort(x.begin(), x.end());
            REP(i, N) {
                cout << (LL)x[i] << endl;
            }
            continue;
        }

        while(B > 0) {
            __int128 S = *min_element(x.begin(), x.end());
            __int128 L = *max_element(x.begin(), x.end());
            if(S * A >= L) {
                break;
            }
            const size_t k = min_element(x.begin(), x.end()) - x.begin();
            x[k] *= A;
            B--;
        }

        sort(x.begin(), x.end());

        if(B == 0) {
            REP(i, N) {
                cout << (LL)(x[i] % 1000000007) << endl;
            }
            continue;
        }

        int time = B / N;
        int rest = B % N;
        for(int i = rest; i < N; i++) {
            mint base = (LL)(x[i] % 1000000007);
            cout << base * (pow(mint(A), time)) << endl;
        }
        for(int i = 0; i < rest; i++) {
            mint base = (LL)(x[i] % 1000000007);
            cout << base * (pow(mint(A), time + 1)) << endl;
        }
    }
    return 0;
}

