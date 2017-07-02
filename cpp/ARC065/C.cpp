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
#define int long long
typedef pair<int, int> Point;

int calcp(Point p) {
    return p.first + p.second;
}

int calcm(Point p) {
    return p.first - p.second;
}

set<int> all_points(const vector<Point>& points, const int D, int a, int b) {
    const int n = points.size();
    map<int, set<pair<Point, int>>> setp; // first + second
    map<int, set<pair<Point, int>>> setm; // first - second
    set<int> res;
    REP(i, n) {
        const auto pt = points[i];
        const int A = calcp(pt);
        setp[A].insert(make_pair(pt, i));
        const int B = calcm(pt);
        setm[B].insert(make_pair(pt, i));
    }
    auto remove = [&](int idx) {
        auto pt = points[idx];
        const int A = calcp(pt);
        setp[A].erase(make_pair(pt, idx));
        const int B = calcm(pt);
        setm[B].erase(make_pair(pt, idx));
    };
    queue<int> que;
    que.push(a); remove(a);
    que.push(b); remove(b);
    while(!que.empty()) {
        const int idx = que.front(); que.pop();
        assert(res.count(idx) == 0);
        res.insert(idx);

        const int x = points[idx].first;
        set<int> next;
        const int A = calcp(points[idx]);
        const int B = calcm(points[idx]);
        {
            const int x1 = x + 0;
            const auto& targets = setp[A + D];

            auto begin = targets.lower_bound(make_pair(Point(x1-1, INT_MAX), INT_MAX));
            for(auto it = begin; it != targets.end(); it ++) {
                const int nidx = it->second;
                const int nx = points[nidx].first;
                assert(x1 <= nx);
                if(nx > x1 + D) { break; }
                next.insert(nidx);
            }
        }
        {
            const int x1 = x - D;
            const auto& targets = setp[A - D];

            auto begin = targets.lower_bound(make_pair(Point(x1-1, INT_MAX), INT_MAX));
            for(auto it = begin; it != targets.end(); it ++) {
                const int nidx = it->second;
                const int nx = points[nidx].first;
                assert(x1 <= nx);
                if(nx > x1 + D) { break; }
                next.insert(nidx);
            }
        }
        {
            const int x1 = x - D;
            const auto& targets = setm[B - D];

            auto begin = targets.lower_bound(make_pair(Point(x1-1, INT_MAX), INT_MAX));
            for(auto it = begin; it != targets.end(); it ++) {
                const int nidx = it->second;
                const int nx = points[nidx].first;
                assert(x1 <= nx);
                if(nx > x1 + D) { break; }
                next.insert(nidx);
            }
        }
        {
            const int x1 = x + 0;
            const auto& targets = setm[B + D];

            auto begin = targets.lower_bound(make_pair(Point(x1-1, INT_MAX), INT_MAX));
            for(auto it = begin; it != targets.end(); it ++) {
                const int nidx = it->second;
                const int nx = points[nidx].first;
                assert(x1 <= nx);
                if(nx > x1 + D) { break; }
                next.insert(nidx);
            }
        }

        for(int nidx : next) {
            que.push(nidx);
            remove(nidx);
        }
    }
    return res;
}

int distance(Point pa, Point pb) {
    return abs(pa.first - pb.first) + abs(pa.second - pb.second);
}

long long get_answer(const vector<Point>& points, const set<int>& idxs, const int D) {
    const int n = points.size();
    map<int, set<pair<Point, int>>> setp_; // first + second
    map<int, set<pair<Point, int>>> setm_; // first - second
    map<int, set<pair<Point, int>>> setp; // first + second
    map<int, set<pair<Point, int>>> setm; // first - second
    set<Point> pointset;
    REP(i, n) {
        const auto pt = points[i];
        const int A = calcp(pt);
        setp_[A].insert(make_pair(pt, i));
        const int B = calcm(pt);
        setm_[B].insert(make_pair(pt, i));
        pointset.insert(pt);
    }
    for(auto p : setp_) {
        int counter = 0;
        set<pair<Point, int>> nset;
        for(auto& x : p.second) {
            auto pt = x.first;
            nset.insert(make_pair(pt, counter++));
        }
        nset.insert(make_pair(Point(1e10, 1e10), counter++));
        setp[p.first] = nset;
    }
    for(auto p : setm_) {
        int counter = 0;
        set<pair<Point, int>> nset;
        for(auto& x : p.second) {
            auto pt = x.first;
            nset.insert(make_pair(pt, counter++));
        }
        nset.insert(make_pair(Point(1e10, 1e10), counter++));
        setm[p.first] = nset;
    }
    
    long long answer = 0;
    for(auto idx : idxs) {
        // cout << "idx: " << idx << endl;
        // cout << "answer: " << answer << "->";
        const int x = points[idx].first;
        const int y = points[idx].second;
        const int A = calcp(points[idx]);
        const int B = calcm(points[idx]);
        if(pointset.count(Point(x+0, y+D))) answer++;
        if(pointset.count(Point(x+0, y-D))) answer++;
        if(pointset.count(Point(x+D, y+0))) answer++;
        if(pointset.count(Point(x-D, y+0))) answer++;
        if(D > 1) {
            {
                const int x1 = x + 1;
                const int x2 = x1 + D-2;
                // x1 <= x2
                const auto& targets = setp[A + D];
                auto begin = targets.lower_bound(make_pair(Point(x1-1, INT_MAX), INT_MAX));
                auto end = targets.lower_bound(make_pair(Point(x2, INT_MAX), INT_MAX));
                // cout << endl;
                // cout << "A+D" << A+D << endl;
                // cout << "x1: " << x1 << " " << x2 << endl;
                // cout << "second: " << end->second << " " << begin->second << endl;
                // cout << "second: " << end->first.first << " " << begin->first.first << endl;
                answer += end->second - begin->second;
            }
            {
                const int x1 = x-D + 1;
                const int x2 = x1 + D-2;
                // x1 <= x2
                const auto& targets = setp[A - D];
                auto begin = targets.lower_bound(make_pair(Point(x1-1, INT_MAX), INT_MAX));
                auto end = targets.lower_bound(make_pair(Point(x2, INT_MAX), INT_MAX));
                answer += end->second - begin->second;
            }
            {
                const int x1 = x-D + 1;
                const int x2 = x1 + D-2;
                // x1 <= x2
                const auto& targets = setm[B - D];
                auto begin = targets.lower_bound(make_pair(Point(x1-1, INT_MAX), INT_MAX));
                auto end = targets.lower_bound(make_pair(Point(x2, INT_MAX), INT_MAX));
                answer += end->second - begin->second;
            }
            {
                const int x1 = x + 1;
                const int x2 = x1 + D-2;
                // x1 <= x2
                const auto& targets = setm[B + D];
                auto begin = targets.lower_bound(make_pair(Point(x1-1, INT_MAX), INT_MAX));
                auto end = targets.lower_bound(make_pair(Point(x2, INT_MAX), INT_MAX));
                answer += end->second - begin->second;
            }
        }
        // cout << answer << endl;
    }
    assert(answer % 2 == 0);
    return answer / 2;
}

signed main(){
    iostream_init();
    int N, a, b;
    while(cin >> N >> a >> b) {
        a--; b--;
        vector<Point> points(N);
        REP(i, N) {
            cin >> points[i].first >> points[i].second;
        }
        auto pa = points[a];
        auto pb = points[b];
        const int D = distance(pa, pb);

        auto idxs = all_points(points, D, a, b);
        cout << get_answer(points, idxs, D) << endl;
    }
    return 0;
}

