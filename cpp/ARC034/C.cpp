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
    cout.setf(ios::fixed);
    cout.precision(12);
}
//}}}

map<int, int> calc(int n) {
    map<int, int> res;
    int m = n;
    for(int i = 2; (LL)i * i <= m; i++) {
        int cnt = 0;
        while(n % i == 0) {
            n /= i;
            cnt++;
        }
        if(cnt > 0) res[i] = cnt;
    }
    if(n != 1) res[n] = 1;
    return res;
}
int main(){
    iostream_init();
    // (B+1) * (B+2) * (B+3) ... * A
    int A, B;
    while(cin >> A >> B) {
        map<int, int> m;
        for(int i = B + 1; i <= A; i++) {
            map<int, int> r = calc(i);
            for(auto p : r) {
                m[p.first] += p.second;
            }
        }
        LL ans = 1;
        const int MOD = 1000000007;
        for(auto p : m) {
            ans *= (p.second + 1);
            ans %= MOD;
        }
        cout << ans << endl;
    }

    return 0;
}

/* vim:set foldmethod=marker: */

