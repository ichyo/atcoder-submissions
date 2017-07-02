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

int main(){
    iostream_init();
    int N;
    cin >> N;
    if(N == 1) {
        cout << "Not Prime" << endl;
        return 0;
    }
    bool prime = true;
    for(int i = 2; i * i <= N; i++) {
        if(N % i == 0) {
            prime = false;
        }
    }

    if(prime) {
        cout << "Prime" << endl;
        return 0;
    }  

    int f = N % 10;
    int sum = 0;
    while(N > 0) {
        sum += N % 10;
        N /= 10;
    }
    if(f % 2 != 0 && f != 5 && sum % 3 != 0) {
        cout << "Prime" << endl;
    } else {
        cout << "Not Prime" << endl;
    }
    return 0;
}

