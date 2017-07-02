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

struct Node{
    map<char, Node*> next;
    Node* fail;
    //vector<int> match;
    bool match;
    Node() : fail(NULL), match(false) {}
    ~Node(){ for(auto p : next) if(p.second) delete p.second; }
};

struct Tree{
    Node* r;
    Tree(vector<string> p) {
        r = build(p);
    }

    Node* get_root() {
        return r;
    }

    Node *build(vector<string> pattens){
        // 1. trie木 をつくる
        Node* root = new Node();
        root->fail = root;
        for(int i = 0; i < pattens.size(); i++){
            Node* p = root;
            for(auto c : pattens[i]){
                if(p->next[c] == 0) p->next[c] = new Node();
                p = p->next[c];
            }
            p->match = true;
            // p->match.push_back(i);
        }

        // 2. failure link を作る
        queue<Node*> que;
        for(int i = 0; i < 128; i++){
            if(!root->next[i]){
                root->next[i] = root;
            }else{
                root->next[i]->fail = root;
                que.push(root->next[i]);
            }

        }
        while(!que.empty()){
            Node* p = que.front(); que.pop();
            for(auto a : p->next) {
                int i = a.first;
                Node* np = a.second;
                if(!np) continue;

                // add que
                que.push(np);

                // search failure link
                Node* f = p->fail;
                while(!f->next[i]) f = f->fail;
                np->fail = f->next[i];

                // update matching list
                // np->match.insert(np->match.end(), np->fail->match.begin(), np->fail->match.end());
                np->match = np->match || np->fail->match;
            }
        }
        return root;
    }

    // Trie木のノード p からの 文字 c に対応する移動先
    Node* next_node(Node* p, char c) const {
        while(!p->next[c]) p = p->fail;
        return p->next[c];
    }

};

namespace{
int N;
int stk_len;
int stk[20];
int L[4];
vector<string> pat;
const int MOD = 1e9 + 7;
void dfs(int k, int r) {
    if(k == 3) {
        string s;
        for(int i = 0; i < stk_len; i++) {
            s += (char)(stk[i] + '0');
        }
        pat.push_back(s);
        return;
    }
    for(int x = 1; x <= r; x++) {
        int nr = r - x;
        int nk = k;
        if(nr == 0) {
            nk = nk + 1;
            nr = L[nk];
        }
        stk[stk_len++] = x;
        dfs(nk, nr);
        stk_len--;
    }
}
map<Node*, int> memo[50];
int pow10[51];
int dfs(const int idx, Node* p, const Tree& t) {
    if(memo[idx].count(p)) return memo[idx][p];
    if(p->match) {
        return memo[idx][p] = pow10[N-idx];
    }
    int& res = memo[idx][p];
    if(idx == N) return res = 0;
    for(int i = 1; i <= 10; i++) {
        Node* np = t.next_node(p, '0' + i);
        res += dfs(idx+1, np, t);
        res %= MOD;
    }
    return res;
}
void init(){
    pow10[0] = 1;
    REP(i, 50) pow10[i+1] = (LL)pow10[i] * 10 % MOD;
}
}
int main(){
    iostream_init();
    init();

    int X, Y, Z;
    while(cin >> N >> X >> Y >> Z) {
        L[0] = X;
        L[1] = Y;
        L[2] = Z;
        pat.clear();
        dfs(0, X);
        Tree tree(pat);
        REP(i, 50) memo[i].clear();
        cout << dfs(0, tree.get_root(), tree) << endl;
    }
    return 0;
}

