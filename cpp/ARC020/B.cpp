#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    REP(i, n) cin >> a[i];
    int ans = n;
    for(int x = 1; x <= 10; x++){
        for(int y = 1; y <= 10; y++){
            int sub = 0;
            if(x == y) continue;
            for(int i = 0; i < n; i++){
                int color = (i % 2 == 0 ? x : y);
                if(a[i] != color) sub++;
            }
            ans = min(ans, sub);
        }
    }
    cout << ans * c << endl;
    return 0;
}

