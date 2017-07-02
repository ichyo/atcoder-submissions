#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

const double EPS = 1e-8;

bool judge(double A, double B, double X, double Y) {
    if(X <= A && Y <= B) return true;
    double d = sqrt(A * A + B * B);
    double rest = (d - Y);
    double len = min(rest * B / A, rest * A / B);
    if(len + EPS >= X) return true;
    return false;
}

int main(){
    double A, B;
    cin >> A >> B;
    int N;
    cin >> N;
    for(int i = 0; i < N; i++) {
        double X, Y;
        cin >> X >> Y;
        if(judge(X, Y, A, B) || judge(Y, X, A, B) ||
            judge(X, Y, B, A) || judge(Y, X, B, A) ) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    } 
    return 0;
}

