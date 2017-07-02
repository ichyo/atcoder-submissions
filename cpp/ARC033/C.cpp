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
struct BITSet{
    BIT bit;
    BITSet(int n) : bit(n) {}
    bool insert(int x) {
        if(count(x) == 1) return false;
        bit.add(x, +1);
        return true;
    }

    bool erase(int x) {
        if(count(x) == 0) return false;
        bit.add(x, -1);
        return true;
    }

    int size() {
        return bit.get(bit.size() - 1);
    }

    void clear() {
        bit = BIT(bit.size());
    }

    int operator[](int idx) {
        if(idx < 0 || idx >= size()) return -1;
        idx ++;
        int x = -1;
        int k = 1;
        while(2 * k < bit.size()){
            k *= 2;
        }
        while(k > 0) {
           if(x + k < bit.size() && bit[x + k] < idx) {
                idx -= bit[x + k];
                x += k;
            }
            k >>= 1;
        }
        return x + 1;
    }

    int index(int x) {
        if(!count(x)) return -1;
        return bit.get(x) - 1;
    }

    int count(int x) {
        return bit.get(x) - bit.get(x - 1);
    }
};
int main(){
    iostream_init();

    int Q;
    cin >> Q;
    const int MAX = 200002;
    BITSet bit(MAX);
    REP(_, Q) {
        int T, X;
        cin >> T >> X;
        if(T == 1) {
            bit.insert(X);
        } else {
            int res = bit[X-1];
            bit.erase(res);
            cout << res << endl;
        }
    }

    return 0;
}

/* vim:set foldmethod=marker: */

