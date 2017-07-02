#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
typedef unsigned long long LL;

LL f(LL n, vector<LL>& a, vector<LL>& b){
    LL cnt = 0;
    REP(i, a.size()) {
        if(n < a[i]) continue;
        cnt += (n - a[i]) / b[i] + 1;
    }
    return cnt;
}

int main(){
    LL K;
    LL N;
    cin >> K >> N;
    vector<LL> a(N), b(N);
    REP(i, N) cin >> a[i] >> b[i];
    LL lb = 0, ub = 1000000000000LL;
    while(ub - lb > 1) {
        LL n = (lb + ub) / 2;
        LL cnt = f(n, a, b);
        if(cnt >= K) {
            ub = n;
        } else{
            lb = n;
        }
    }
    LL n = ub - 1;
    // cout << n << endl;
    LL cnt = f(n, a, b);
    // cout << cnt << endl;
    LL rest = K - cnt;
    assert(rest > 0);
    LL ans = 0;
    for(int i = 0; i < N; i++){
        if(n < a[i]) continue;
        LL c = (n - a[i]) / b[i] + 1;
        ans += c * (2 * a[i] + (c - 1) * b[i]) / 2;
    }
    ans += rest * (n + 1);
    cout << ans << endl;
    return 0;
}

