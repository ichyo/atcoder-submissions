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

double calc(int A, int C, double ave) {
    double res = 0;
    if(A > 0) {
        res += 1.0 * A / (A + C) * (ave + calc(A-1, C, ave));
    }

    res += 1.0 * A / (A + C) * (0);

    return res;
}
double calc2(int B, int C, double ave, int A0, int A1) {
    double res = 0;
    if(A0 > 0) {
        res == 1.0 * A0 / (A0 + B + C) * (calc2(B, C, ave, A0-1, A1));
    } 
    if(B > 0) {
        res += 1.0 * B / (A0 + B + C) * ((ave * (A1-A0) / A1 + (1.0 * A0/A1)) * calc2(B-1, C, ave, A0, A1));
    }

    res += 1.0 * C / (A0 + B + C) * (1);

    return res;
}

int main(){
    iostream_init();

    int A, B, C;
    while(cin >> A >> B >> C) {
        vector<double> a(A);
        vector<double> b(B);
        REP(i, A) cin >> a[i];
        REP(i, B) cin >> b[i];

        double sumA = 0;
        REP(i, A) sumA += a[i];

        double mulB = 1.0;
        REP(i, B) mulB *= b[i];

        // double X = sumA / A;
        // double Y = pow(mulB, 1.0 / B);


        double SA = calc(A, C, 1.0 * sumA / A);
        double SB = calc2(B, C, pow(mulB, 1.0 / B), A, A);
        
        cout << SA << " " << SB << endl;
        
        double SC = SA * SB;
        cout << SC << endl;
    }

    return 0;
}

/* vim:set foldmethod=marker: */

