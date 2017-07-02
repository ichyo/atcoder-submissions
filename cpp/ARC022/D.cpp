#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
int sq(int x, int y){
    return x * x + y * y;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> cx(N), cy(N);
        REP(i, N) cin >> cx[i] >> cy[i];
        assert(N <= 100);
        int res = 0;
        for(int y = -305; y <= 305; y++){
            for(int x = -305; x <= 305; x++){
                for(int i = 0; i < N; i++){
                    if(sq(x - cx[i], y - cy[i]) <= sq(cx[i], cy[i])){
                        res++;
                        break;
                    }
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}

