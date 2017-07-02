#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> a(N);
    REP(i, N){
        cin >> a[i];
    }
    vector<int> cnt(100001, 0);
    int ans = 0;
    for(int b = 0, e = 0; b < N && e < N; b++){
        while(e < N && cnt[a[e]] == 0){
            cnt[ a[e] ]++;
            e++;
        }
        ans = max(ans, e - b);
        cnt[ a[b] ]--;
    }
    cout << ans << endl;
    return 0;
}

