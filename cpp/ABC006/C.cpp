#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
bool calc(int n, int m, int& a, int& b, int& c){
    int k = m - 2 * n;
    for(int C = 0; 2 * C <= k; C++){
        int B = k - 2 * C;
        int A = n - B - C;
        if(A >= 0 && B >= 0 && C >= 0){
            a = A, b = B, c = C;
            return true;
        }
    }
    return false;
}

int main(){
    int n, m;
    cin >> n >> m;
    int a, b, c;
    if(calc(n, m, a, b, c)){
        cout << a << " " << b << " " << c << endl;
    }else{
        cout << "-1 -1 -1" << endl;
    }
    return 0;
}

