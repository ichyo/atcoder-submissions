#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

int main(){
    int T;
    cin >> T;
    while(T--) {
        string a, b;
        cin >> a >> b;
        int C[26] = {};
        for(char c : a) C[c - 'a']++;
        bool ans = false;
        for(char c : b)  if(C[c - 'a']) ans = true;
        cout << (ans ? "YES" : "NO") << endl;
    }
    return 0;
}

