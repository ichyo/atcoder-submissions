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

const int d[6][4] = {
    {0, 1, 2, 3},
    {0, 5, 4, 1},
    {1, 4, 7, 2},
    {2, 7, 6, 3},
    {4, 5, 6, 7},
    {5, 0, 3, 6},
};
int main(){
    iostream_init();
    int N;
    while(cin >> N) {
        int C[500][4] = {};
        REP(i, N) REP(j, 4) cin >> C[i][j];

        map<array<int, 4>, int> count;
        REP(i, N) {
            array<int, 4> a;
            REP(j, 4) a[j] = C[i][j];
            count[a] += 1;
        }

        set<array<int, 8>> colors;
        REP(i, N) REP(j, N) if(i != j) REP(rot1, 4) REP(rot2, 4) {
            array<int, 8> c;
            REP(k, 4) c[k] = C[i][(k + rot1) % 4];
            REP(k, 4) c[4 + k] = C[j][(k + rot2) % 4];
            colors.insert(c);
        }

        mint answer = 0;

        array<int, 4> c[6];
        int cnt = 0;

        for(const auto& color : colors) {
            array<int, 4> cs;
            vector<int> rots1; REP(rot, 4){ REP(j, 4) cs[j] = color[ d[0][(j + rot) % 4] ]; if(count[cs]) rots1.push_back(rot); }
            if(!rots1.size()) continue;
            vector<int> rots2; REP(rot, 4){ REP(j, 4) cs[j] = color[ d[1][(j + rot) % 4] ]; if(count[cs]) rots2.push_back(rot); }
            if(!rots2.size()) continue;
            vector<int> rots3; REP(rot, 4){ REP(j, 4) cs[j] = color[ d[2][(j + rot) % 4] ]; if(count[cs]) rots3.push_back(rot); }
            if(!rots3.size()) continue;
            vector<int> rots4; REP(rot, 4){ REP(j, 4) cs[j] = color[ d[3][(j + rot) % 4] ]; if(count[cs]) rots4.push_back(rot); }
            if(!rots4.size()) continue;
            vector<int> rots5; REP(rot, 4){ REP(j, 4) cs[j] = color[ d[4][(j + rot) % 4] ]; if(count[cs]) rots5.push_back(rot); }
            if(!rots5.size()) continue;
            vector<int> rots6; REP(rot, 4){ REP(j, 4) cs[j] = color[ d[5][(j + rot) % 4] ]; if(count[cs]) rots6.push_back(rot); }
            if(!rots6.size()) continue;

            for(int rot1 : rots1) { REP(j, 4) c[0][j] = color[ d[0][(j + rot1) % 4] ]; 
            for(int rot2 : rots2) { REP(j, 4) c[1][j] = color[ d[1][(j + rot2) % 4] ]; 
            for(int rot3 : rots3) { REP(j, 4) c[2][j] = color[ d[2][(j + rot3) % 4] ]; 
            for(int rot4 : rots4) { REP(j, 4) c[3][j] = color[ d[3][(j + rot4) % 4] ]; 
            for(int rot5 : rots5) { REP(j, 4) c[4][j] = color[ d[4][(j + rot5) % 4] ]; 
            for(int rot6 : rots6) { REP(j, 4) c[5][j] = color[ d[5][(j + rot6) % 4] ]; 
                {
                    mint sub = 1;
                    int max_i = 0;
                    REP(i, 6) {
                        if(count[ c[i] ] > 0) {
                            sub *= mint(count[c[i]]);
                        } else {
                            sub = 0;
                            break;
                        }
                        max_i = i;
                        count[ c[i] ]--;
                    }
                    REP(i, max_i+1) { count[ c[i] ]++; }

                    answer += sub;
                }
            }}}}}}}

        answer /= mint(24);

        cout << answer.val << endl;
    }
    return 0;
}
