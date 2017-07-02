#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

int main(){
    string s;
    cin >> s;
    string t = s;
    reverse(t.begin(), t.end());
    cout << (s == t ? "YES" : "NO") << endl;
    return 0;
}

