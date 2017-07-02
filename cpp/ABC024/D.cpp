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
int main(){
    iostream_init();
    LL A, B, C;
    cin >> A >> B >> C;
    const LL MOD = 1e9 + 7;
    B = inv_mod(B, MOD);
    C = inv_mod(C, MOD);
    for(int S = 1; ; S++) {
        int r = (A * S % MOD * C % MOD);
        int c = (A * S % MOD * B % MOD);
        if(r + c == S + 1) {
            cout << r-1 << " " << c-1 << endl;
            break;
        }
    }
    return 0;
}

/* vim:set foldmethod=marker: */

