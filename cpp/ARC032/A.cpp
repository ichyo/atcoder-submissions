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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
inline bool valid(int x, int w) { return 0 <= x && x < w; }

void iostream_init() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
//}}}

bool is_prime(int n) {
    if(n <= 1) return false;
    for(int i = 2; (long long)i*i <= n; i++) {
        if(n % i == 0) return false;
    }
    return true;
}
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

// mod * mod が long long に収まらない場合，
// 足し算でオーバーフローを避けてO(log b)で計算する
// mod * mod が long long に収まるときはreturn a * b % mod;に書き換える
LL mul_mod(LL a, LL b, LL mod){
    if(b == 0) return 0;
    LL res = mul_mod((a + a) % mod, b / 2, mod);
    if(b & 1) res = (res + a) % mod;
    return res;
}

// aのb乗をmodで割った余りをO(log b)で計算する
LL pow_mod(LL a, LL b, LL mod){
    if(b == 0) return 1;
    LL res = pow_mod(mul_mod(a, a, mod), b / 2, mod);
    if(b & 1) res = mul_mod(res, a, mod);
    return res;
}

// a * b % mod == 1 をみたすbを計算する．計算量はO(log mod)
// modが素数のときは b = a ^ (mod - 2)でも計算できる
LL inv_mod(LL a, LL mod){
    LL x, y;
    extgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

// 素数pを法とする，1..nの逆元のリストを求める． 計算量はO(n)
vector<LL> inverse_list(int n, int p){
    vector<LL> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i){
        inv[i] = inv[p % i] * (p - p / i) % p;
    }
    return inv;
}
bool miller_rabin(LL n){
    if(n == 2) return true;
    if(n % 2 == 0 || n <= 1) return false;

    vector<LL> a = {2, 3, 5, 7, 11, 13, 17};

    LL d = n - 1, s = 0;
    while((d & 1) == 0){
        d >>= 1;
        s++;
    }

    for(int i = 0; i < a.size() && a[i] < n; i++){
        LL x = pow_mod(a[i], d, n);
        if(x == 1) continue;
        for(int r = 0; r < s; r++){
            if(x == n - 1) break;
            if(r + 1 == s) return false;
            x = mul_mod(x, x, n);
        }
    }

    return true;
}

int main(){
    iostream_init();
    LL n;
    cin >> n;
    LL p = 0;
    REP(i, n) p += i + 1;
    cout << (miller_rabin(n) ? "WANWAN" : "BOWWOW") << endl;
    return 0;
}

/* vim:set foldmethod=marker: */

