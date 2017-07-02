#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

int main(){
    int n, k;
    cin >> n >> k;
    if(k == 1) {
        cout << "YES" << endl;
    } else {
        cout << (n >= 2*k ? "YES" : "NO") << endl;
    }
    return 0;
}

