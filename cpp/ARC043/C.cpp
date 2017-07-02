// Template {{{
#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

#ifdef LOCAL
#include "contest.h"
#else
#define dump(x) 
#endif

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
typedef tuple<int, int, int> Data;
typedef long long LL;
struct BIT{
    vector<LL> sums;
    BIT(int n) : sums(n) {}

    // v[at] += by
    void add(int at, LL by) {
        while(at < sums.size()){
            sums[at] += by;
            at |= at + 1;
        }
    }

    // v[0] + ... + v[at]
    LL get(int at) {
        LL res = 0;
        while(at >= 0) {
            res += sums[at];
            at = (at & (at + 1)) - 1;
        }
        return res;
    }

    // --- optional ---
    int size() const { return sums.size(); }
    LL operator [](int idx) const { return sums[idx]; }
};
LL inversion_number(vector<int> v) {
    int n = (int)v.size();
    BIT bit(n + 10);
    LL res = 0;
    for(int i = (int)v.size()-1; i >= 0; i--) {
        res += bit.get(v[i]);
        bit.add(v[i], 1);
    }
    return res;
}
vector<int> slow(vector<Data> data) {
    int n = data.size();

    LL inv;
    {
        vector<int> b(n);
        REP(i, n) b[i] = get<1>(data[i]);
        inv = inversion_number(b);
    }

    if(inv % 2 == 1) {
        return vector<int>();
    }

    if(inv == 0) { goto END; }

    for(int i = 0; i < n; i++) {
        for(int j = n-1; j-1 >= i; j--) {
            swap(data[j], data[j-1]);
            if(get<1>(data[j-1]) < get<1>(data[j])) {
                inv -= 2;
            }
            if(inv == 0) { goto END; }
        }
    }
END:
    assert(inv == 0);
    vector<int> res(n);
    REP(i, res.size()) res[i] = get<2>(data[i]);
    return res;
}
vector<int> fast(vector<Data> data) {
    int n = data.size();

    vector<int> b(n);
    vector<int> c(n);
    REP(i, n) b[i] = get<1>(data[i]);
    REP(i, n) c[i] = get<2>(data[i]);
    LL inv = inversion_number(b);

    if(inv % 2 == 1) {
        return vector<int>();
    }

    BIT bit(n + 10);
    REP(i, n) bit.add(b[i], 1);

    vector<int> res;

    for(int i = 0; i < n; i++) {
        LL ninv = inv - (bit.get(n+9) - bit.get(b[n-1-i])) * 2;
        bit.add(b[n-1-i], -1);
        if(ninv > 0) {
            inv = ninv;
            res.push_back(c[n-1-i]);
        } else {
            for(int j = n-1-i; j-1 >= 0; j--) {
                swap(b[j], b[j-1]);
                swap(c[j], c[j-1]);
                if(b[j-1] < b[j]) {
                    inv -= 2;
                }
                if(inv == 0) { break; }
            }
            for(int j = 0; j <= n-1-i; j++) {
                res.push_back(c[j]);
            }
            break;
        }
    }

    assert(res.size() == n);
    return res;
}
int main(){
    iostream_init();
    int N;
    while(cin >> N) {
        vector<int> A(N);
        vector<int> B(N);
        REP(i, N) cin >> A[i];
        REP(i, N) cin >> B[i];
        map<int, int> inv_A, inv_B;
        REP(i, N) inv_A[A[i]] = i+1;
        REP(i, N) inv_B[B[i]] = i+1;
        vector<Data> data(N);
        REP(i, N) {
            data[i] = make_tuple(inv_A[i+1], inv_B[i+1], i+1);
        }
        sort(data.begin(), data.end());
        vector<int> res = fast(data);
        if(res.size() == 0) {
            cout << -1 << endl;
        } else {
            REP(i, res.size()) {
                cout << res[i] << " \n"[i == res.size()-1];
            }
        }
    }
    return 0;
}

/* vim:set foldmethod=marker: */

