#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int a[7], b[7];
    REP(i, 7) cin >> a[i];
    REP(i, 7) cin >> b[i];
    int sum = 0;
    REP(i, 7) {
        sum += max(a[i], b[i]);
    }
    cout << sum << endl;
    return 0;
}

