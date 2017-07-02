#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
int calc(int n){
    if(n == 1) return 0;
    if(n == 2) return 0;
    int cur = 1, prev1 = 0, prev2 = 0;
    REP(i, n - 3){
        int next = (cur + prev1 + prev2) % 10007;
        prev2 = prev1;
        prev1 = cur;
        cur = next;
    }
    return cur;
}

int main(){
    int n;
    cin >> n;
    cout << calc(n) << endl;
    return 0;
}

