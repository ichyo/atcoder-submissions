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
    UnionFind(int N) : data(N, -1) { }
    // xとyを併合する
    bool unite(int x, int y) {
        x = root(x); y = root(y);
        if (x != y) {
            if (data[x] > data[y]) swap(x, y);
            data[x] += data[y]; data[y] = x;
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
    int N, K, L;
    while(cin >> N >> K >> L) {
        UnionFind uf1(N);
        UnionFind uf2(N);
        REP(i, K) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            uf1.unite(a, b);
        }
        REP(i, L) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            uf2.unite(a, b);
        }
        unordered_map<LL, vector<int>> m;
        REP(i, N) {
            int t1 = uf1.root(i);
            int t2 = uf2.root(i);
            LL x = ((LL)t1) << 32 | t2;
            m[x].push_back(i);
        }
        vector<int> answer(N);
        for(auto p : m) {
            int size = p.second.size();
            for(auto x : p.second) {
                answer[x] = size;
            }
        }
        REP(i, N) {
            cout << answer[i];
            if(i != N-1) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    }
    return 0;
}

