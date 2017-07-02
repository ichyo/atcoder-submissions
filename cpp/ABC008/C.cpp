#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int N;
    vector<int> v(N);
    REP(i, N) cin >> v[i];
    for(int i = 0; i < N; i++) {
        int cnt = 0;
        for(int j = 0; j < N; j++) {
            if(v[i] % v[j] == 0) {
                cnt++;
            }
        }

        double expect = 0;
        for(int j = 0; j < N; j++) {
        }
    }
    return 0;
}

