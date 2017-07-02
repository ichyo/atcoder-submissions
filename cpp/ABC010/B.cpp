#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int n;
    cin >> n;
    int ans = 0;
    REP(i, n) {
        int t;
        cin >> t;
        while(t > 0 && (t % 2 == 0 || t % 3 == 2)) {
            t--;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}

