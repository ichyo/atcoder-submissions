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

struct UnionFind {
    vector<int> data;
    vector<vector<int>> to;
    UnionFind(int N) : data(N, -1), to(N) { }
    // xとyを併合する
    bool unite(int x, int y) {
        x = root(x); y = root(y);
        if (x != y) {
            if (data[x] > data[y]) swap(x, y);
            data[x] += data[y]; data[y] = x;

            if(to[x].size() < to[y].size()) to[x].swap(to[y]);
            for(auto it = to[y].begin(); it != to[y].end(); ) {
                if(*it != x) to[x].push_back(*it);
                it = to[y].erase(it);
            }
        }
        return x != y;
    }
    // xとyが同じ集合にあるか判定する
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    // xを含む集合の要素数を求める
    int size(int x) {
        return -data[root(x)];
    }
    int root(int x) {
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }
};

int main(){
    iostream_init();
    int N, Q;
    while(cin >> N >> Q) {
        UnionFind uf(2 * N);
        REP(i, Q) {
            int w, a, b, cost;
            cin >> w >> a >> b >> cost;
            a--;
            b--;
            cost %= 2;
            if(w == 1) {
                if(cost == 0) {
                    uf.unite(2*a, 2*b);
                    uf.unite(2*a + 1, 2*b + 1);
                } else {
                    uf.unite(2*a + 1, 2*b);
                    uf.unite(2*a, 2*b + 1);
                }
            } else {
                cout << (uf.same(2*a, 2*b) || uf.same(2*a+1, 2*b+1) ? "YES" : "NO") << endl;
            }
        }
    }
    return 0;
}

/* vim:set foldmethod=marker: */

