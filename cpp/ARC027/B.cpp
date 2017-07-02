#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int uf[100];
int root(int x) {
    if(uf[x] == x) return x;
    return uf[x] = root(uf[x]);
}

int main(){
    int N;
    while(cin >> N){
        REP(i, N) uf[i] = i;
        string s1, s2;
        cin >> s1 >> s2;
        REP(i, N) REP(j, N) if(i < j && !isdigit(s1[i]) && s1[i] == s1[j]) {
            int x = root(i);
            int y = root(j);
            if(x == y) continue;
            uf[x] = y;
        }
        REP(i, N) REP(j, N) if(i < j && !isdigit(s2[i]) && s2[i] == s2[j]) {
            int x = root(i);
            int y = root(j);
            if(x == y) continue;
            uf[x] = y;
        }
        REP(i, N) REP(j, N) if(i != j && !isdigit(s1[i]) && s1[i] == s2[j]) {
            int x = root(i);
            int y = root(j);
            if(x == y) continue;
            uf[x] = y;
        }
        set<int> digit[100];
        REP(i, N) if(isdigit(s1[i])) digit[ root(i) ].insert(s1[i]);
        REP(i, N) if(isdigit(s2[i])) digit[ root(i) ].insert(s2[i]);
        long long ans = 1;
        REP(i, N) {
            if(i == root(i)){
                int s = digit[i].size();
                if(s == 0) {
                    ans *= (root(i) == root(0) ? 9 : 10);
                } else if(s != 1) {
                    //ans *= 0;
                }
            }
        }
        assert(ans != 0);
        cout << ans << endl;
    }
    return 0;
}

