#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int N;
    while(cin >> N){
        const int B = 2500;
        vector<int> cx(N), cy(N);
        REP(i, N) cin >> cx[i] >> cy[i];
        int res = 0;
        for(int y = -B; y <= B; y++){
            vector<int> grid(2 * B + 10);
            for(int i = 0; i < N; i++){
                int norm = cx[i] * cx[i] + cy[i] * cy[i];
                int dy = y - cy[i];
                if(dy * dy <= norm){
                    int dx = sqrt(norm - dy * dy);
                    grid[cx[i] - dx + B] ++;
                    grid[cx[i] + dx + 1 + B] --;
                }
            }
            for(int x = 1; x < 2 * B; x++){
                grid[x] += grid[x - 1];
                if(grid[x] > 0){ 
                    res++;
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}

