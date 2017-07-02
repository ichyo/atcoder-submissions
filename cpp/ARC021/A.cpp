#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int A[4][4];
    REP(y, 4) REP(x, 4) cin >> A[y][x];
    bool ok = false;
    REP(y, 4) REP(x, 3) if(A[y][x] == A[y][x + 1]) ok = true;
    REP(y, 3) REP(x, 4) if(A[y][x] == A[y + 1][x]) ok = true;
    cout << (ok ? "CONTINUE" : "GAMEOVER") << endl;
    return 0;
}

