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
    ModInt(unsigned x):val(x){}
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
        if(u < 0) u += Mod;
        return ModInt(u);
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
};
template<int MOD>
ostream& operator << (ostream& os, const ModInt<MOD> m) {
    return os << m.val;
}
// }}}
typedef ModInt<1000000007> mint;

// [2, N] の範囲の素数を列挙する
vector<int> all_primes(int N) {
    vector<bool> b(N+1, true);
    vector<int> res;
    for(int i = 2; i <= N; i++) {
        if(!b[i]) continue;
        res.push_back(i);
        if((LL)i*i > N) continue;
        for(int j=i*i; j <= N; j+=i) {
            b[j] = false;
        }
    }
    return res;
}

// 整数 N の約数を列挙する O(sqrt(N))
vector<LL> divisor(LL N) {
    vector<LL> res;
    for(LL i = 1; i*i <= N; i++) {
        if(N % i != 0) continue;
        res.push_back(i);
        if(i != N/i) res.push_back(N/i);
    }
    sort(res.begin(), res.end());
    return res;
}

map<LL, int> factorize(LL N, const vector<int>& primes) {
    // assert(primes is superset of all_primes(sqrt(N)))
    // assert(primes is sorted)
    map<LL, int> res;
    for(auto p : primes) {
        if((LL)p*p > N) break;
        if(N % p != 0) continue;
        int c = 0;
        while(N % p == 0) {
            c++;
            N /= p;
        }
        res[p] = c;
    }
    if(N > 1) res[N] = 1;
    return res;
}

mint sumup(int N) {
    mint all = (LL)N*(N-1)/2;
    return all;
}

mint calc(int K, int B, const vector<int>& f) {
    // sum {x | x < B and gcd(x, K) == 1}
    mint res = 0;
    for(int s : range(1<<f.size())) {
        int p = 1;
        for(int i : range(f.size())) if(s >> i & 1) {
            p *= f[i];
        }
        if(K % p != 0) continue;
        int sign = (__builtin_popcount(s) % 2 ? -1 : +1);
        mint diff = sumup((B+p-1)/p) * p * sign;
        res += diff;
    }
    return res;
}

unsigned solve(int N, int K) {
    N++;

    mint ans = 0;
    auto primes = all_primes(1e5);
    auto fact = factorize(K, primes);
    for(auto p : fact) dump(p);

    vector<int> f;
    for(auto p : fact) f.push_back(p.first);

    for(auto d : divisor(K)) {
        // gcd(i, K) == d, i < N
        // gcd(j, K/d) == 1, j < N/d
        ans += calc(K/d, (N+d-1)/d, f) * K;
    }

    return ans.val;

}
int main(){
    iostream_init();
    int N, K;
    while(cin >> N >> K) {
        cout << solve(N, K) << endl;
    }
    return 0;
}

/* vim:set foldmethod=marker: */

