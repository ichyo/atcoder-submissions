#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int A, B;
    cin >> A >> B;
    A = abs(A);
    B = abs(B);
    if(A < B){
        cout << "Ant" << endl;
    }else if(A > B){
        cout << "Bug" << endl;
    }else{
        cout << "Draw" << endl;
    }
    return 0;
}

