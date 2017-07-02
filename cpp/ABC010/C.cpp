#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
double dist(int x, int y){
    return sqrt(x * x + y * y);
}
double EPS = 1e-8;
int main(){
    int x1, y1, x2, y2, T, V;
    cin >> x1 >> y1 >> x2 >> y2 >> T >> V;
    int n;
    cin >> n;
    bool ans = false;
    REP(i, n) {
        int a, b;
        cin >> a >> b;
        double d = dist(x1 - a, y1 - b) + dist(x2 - a, y2 - b);
        if(d - EPS < V * T){
            ans = true;
        }
    }
    if(ans) {
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
    return 0;
}

