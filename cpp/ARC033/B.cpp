// Template {{{
#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

template<typename T1, typename T2>
ostream& operator << (ostream& os, const pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream& os, const vector<T>& v) {
    os << "{";
    for(int i = 0; i < v.size(); i++)
        os << v[i] << (i+1<v.size()?", ":"");
    os << "}";
    return os;
}

class range {
  struct Iterator {
    int val, inc;
    int operator*() {return val;}
    bool operator!=(Iterator& rhs) {return val < rhs.val;}
    void operator++() {val += inc;}
  };
  Iterator i, n;
public:
  range(int e) : i({0, 1}), n({e, 1}) {}
  range(int b, int e) : i({b, 1}), n({e, 1}) {}
  range(int b, int e, int inc) : i({b, inc}), n({e, inc}) {}
  Iterator& begin() {return i;}
  Iterator& end() {return n;}
};

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
inline bool valid(int x, int w) { return 0 <= x && x < w; }

void iostream_init() {
    ios::sync_with_stdio(false);
    cin.tie(0);
}
//}}}

int include(const vector<int>& A, const vector<int>& B) {
    int i = 0, j = 0;
    int res = 0;
    while(i < A.size() && j < B.size()) {
        if(A[i] < B[j]) {
            i++;
        } else if(A[i] > B[j]) {
            j++;
        } else {
            i++; j++;
            res++;
        }
    }
    return res;
}
int main(){
    iostream_init();
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    vector<int> B(M);
    REP(i, N) cin >> A[i];
    REP(i, M) cin >> B[i];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    int inc = include(A, B);
    int out = A.size() + B.size() - inc;
    double ans = 1.0 * inc / out;
    printf("%.12f\n", ans);

    return 0;
}

/* vim:set foldmethod=marker: */

