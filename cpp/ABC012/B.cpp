#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int n;
    cin >> n;
    int s = n % 60;
    n /= 60;
    int m = n % 60;
    n /= 60;
    int h = n;
    printf("%02d:%02d:%02d\n", h, m, s);
    return 0;
}

