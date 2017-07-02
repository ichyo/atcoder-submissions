#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
typedef long long LL;
inline LL mul_mod(LL a, LL b, LL mod){
    return a * b % mod;
}
LL pow_mod(LL a, LL b, LL mod){
    if(b == 0) return 1;
    LL res = pow_mod(mul_mod(a, a, mod), b / 2, mod);
    if(b & 1) res = mul_mod(res, a, mod);
    return res;
}
// a....a (d times)
LL len(LL n){
    LL res = 0;
    while(n > 0){
        n /= 10;
        res++;
    }
    return res;
}
LL calc(LL a, LL d, LL mod, LL len){
    if(d == 0) return 0;
    if(d == 1) return a;
    LL c = calc(a, d / 2, mod, len);
    LL c2 = c * pow_mod(10, (d/2) * len, mod) % mod;
    LL res = (c + c2) % mod;
    if(d % 2 == 1){
        res = res * pow_mod(10, len, mod) % mod;
        res = (res + a) % mod;
    }
    return res;
}
int main(){
    int N, B;
    cin >> N;
    vector<LL> a(N), L(N);
    REP(i, N) cin >> a[i] >> L[i];
    cin >> B;
    LL digit = 0;
    LL ans = 0;
    for(int i = N - 1; i >= 0; i--){
        LL result = calc(a[i], L[i], B, len(a[i]));
        result = result * pow_mod(10, digit, B) % B;
        ans = (ans + result) % B;
        digit += L[i] * len(a[i]);
    }
    cout << ans << endl;
    return 0;
}

