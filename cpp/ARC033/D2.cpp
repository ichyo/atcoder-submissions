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
}
//}}}

static const unsigned MODVAL = 1000000007;
LL extgcd(LL a, LL b, LL& x, LL& y){
    LL d = a;
    if(b != 0){
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }else{
        x = 1; y = 0;
    }
    return d;
}
LL inv_mod(LL a, LL mod){
    LL x, y;
    extgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}
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
mint& operator/=(mint& x, mint y) { return x = LL(x.val)*inv_mod(y.val, MODVAL); }
mint operator+(mint x, mint y) { return x+=y; }
mint operator-(mint x, mint y) { return x-=y; }
mint operator*(mint x, mint y) { return x*=y; }
mint operator/(mint x, mint y) { return x/=y; }
int main(){
    iostream_init();
    int N;
    while(cin >> N) {
        const int MOD = 1000000007;
        N++;
        // assert(N <= 3030);

        vector<int> P(N);
        REP(i, N) {
            cin >> P[i];
        }

        int T;
        cin >> T;

        if(T < N) {
            cout << P[T] << endl;
            continue;
        } else {
            int L = 1;
            REP(i, N) L = (LL)L * (T - i) % MOD;

            vector<int> pre_inv(4 * N);
            REP(i, 4 * N) pre_inv[i] = inv_mod(i - 2 * N + MOD, MOD);

            int ans = 0;
            int Y = 1;
            REP(j, N) if(0 != j) Y = (LL)Y * pre_inv[0 - j + 2 * N] % MOD;

            REP(i, N) {
                int X = L;
                X = (LL)X * inv_mod(T - i, MOD) % MOD;
                X = (LL)X * Y % MOD;
                ans += (LL)P[i] * X % MOD;
                ans %= MOD;

                Y = (LL)Y * pre_inv[i+1 - 0 + 2 * N] % MOD;
                Y = (LL)Y * (i - (N - 1) + MOD) % MOD;
            }

            cout << ans << endl;
        }
    }

    return 0;
}

/* vim:set foldmethod=marker: */

