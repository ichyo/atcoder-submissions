#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int sum = 2013 + 12;
    int n;
    cin >> n;
    n = sum - n;
    for(int i = 1; i <= 9; i++){
        for(int j = 1; j <= 9; j++){
            if(i * j == n) {
                printf("%d x %d\n", i, j);
            }
        }
    }
    return 0;
}

