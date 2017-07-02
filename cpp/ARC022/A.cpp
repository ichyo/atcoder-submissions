#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    string s;
    cin >> s;
    REP(i, s.size()) if(islower(s[i])) s[i] = s[i] - 'a' + 'A';
    string ICT = "ICT$";
    int k = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == ICT[k]){
            k++;
        }
    }
    if(k == 3){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
    return 0;
}

