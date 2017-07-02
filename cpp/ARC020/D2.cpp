#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;

void make_dict(int K, map<vector<int>, int>& time_dict){
    vector<int> perm(K);
    REP(i, K) perm[i] = i;
    do{
        vector<int> time(K - 1);
        for(int i = 0; i + 1 < K; i++){
            int from = perm[i], to = perm[i + 1];
            if(from > to) swap(from, to);
            for(int j = from; j < to; j++){
                time[j] ++;
            }
        }
        time_dict[time]++;
    }while(next_permutation(perm.begin(), perm.end()));
}

int main(){
    map<vector<int>, int> time_dict;
    make_dict(10, time_dict);
    cout << "{";
    for(auto& p : time_dict){
        cout << "{";
        cout << "{";
        REP(i, p.first.size()){
            cout << p.first[i];
            if(i == p.first.size() - 1){
                cout << "}, ";
            }else{
                cout << ", ";
            }
        }
        cout << p.second << "}, ";
    }
    cout << "}" << endl;
    return 0;
}

