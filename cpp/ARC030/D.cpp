#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)
using namespace std;
typedef long long LL;

struct SegTree{
    int N;
    vector<LL>all, part;
    SegTree(int size) {
        N = 1;
        while(N < size) {
            N *= 2;
        }
        all=part=vector<LL>(2*N);
    }

    void add(int x, int y, LL v) { add(x, y, 1, 0, N, v); }
    void add(int x, int y, int k, int l, int r, LL v) {
        if (x<=l && r<=y) {
            all[k] += v;
        } else if (x<r && l<y) {
            part[k] += (min(y, r) - max(x, l)) * v;
            add(x, y, k*2, l, (l+r)/2, v);
            add(x, y, k*2+1,  (l+r)/2, r, v);
        }
    }
    LL sum(int a, int b) {
        return sum(a, b, 1, 0, N);
    }
    LL sum(int a, int b, int k, int l, int r) {
        if (b <= l || r <= a){ //[a, b)と[l, r)が全く交差しない場合
            return (0);
        }
        else if (a <= l && r <= b){ //完全に内包されていれば
            return (all[k] * (r - l) + part[k]);
        }
        else { //[l, r)と[a, b)が交差していれば
            ll res;
            res = (min(b, r) - max(a, l)) * all[k]; //そのノードの全ての要素が持つ値のうち, [a, b)に属すものの分だけを加算する.
            res += sum(a, b, k * 2 + 1, l, (l + r) / 2);
            res += sum(a, b, k * 2 + 2, (l + r) / 2, r);
            return (res);
        }
    }

    void update(int a, int b, int l, int r) {
        L += N;
        R += N;
        for (;L<R; L>>=1, R>>=1) {
        if(R&1) --R; //--Rが対応するインデックス
        if(L&1) L++; //L++が対応するインデックス
        }
    }
};

int main(){
    int N, Q;
    while(cin >> N >> Q) {
        vector<int> x(N);
        REP(i, N) cin >> x[i];
        REP(i, Q) {
            int type;
            cin >> type;
            if(type == 1) {
            } else if(type == 2) {
            } else if(type == 3) {
            }
        }
    }
    return 0;
}

