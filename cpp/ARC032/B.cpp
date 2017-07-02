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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
inline bool valid(int x, int w) { return 0 <= x && x < w; }

void iostream_init() {
    ios::sync_with_stdio(false);
    cin.tie(0);
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
    int n, m;
    while(cin >> n >> m) {
        int ans = n - 1;
        UnionFind uf(n);
        REP(i, m) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            if(uf.unite(a, b)) {
                ans--;
            }
        }
        cout << ans << endl;
    }

    return 0;
}

/* vim:set foldmethod=marker: */

