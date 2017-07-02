#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
const int inf = 99999999;
#define index_of(as, x) \
  distance(as.begin(), lower_bound(as.begin(), as.end(), x))
vector<int> lis_fast(const vector<int>& a) {
  const int n = a.size();
  vector<int> A(n, inf);
  vector<int> id(n);
  for (int i = 0; i < n; ++i) {
    id[i] = index_of(A, a[i]);
    A[ id[i] ] = a[i];
  }
  int m = *max_element(id.begin(), id.end());
  vector<int> b(m+1);
  for (int i = n-1; i >= 0; --i)
    if (id[i] == m) b[m--] = a[i];
  return b;
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    REP(i, n) cin >> a[i];
    int s = lis_fast(a).size();
    cout << n - s << endl;
    return 0;
}

