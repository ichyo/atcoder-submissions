#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int h, m;
    cin >> h >> m;
    int ans = 60 - m;
    ans += (18 - h - 1) * 60;
    cout << ans << endl;
    return 0;
}

