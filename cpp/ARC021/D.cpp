#include <bits/stdc++.h>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
namespace LSH {
  using namespace std;

  template<class T, int min = 0, int max = numeric_limits<typename T::result_type>::max()>
  typename T::result_type rand() {
    static mt19937 engine;
    static T distribution(min, max);
    return distribution(engine);
  }
	
  // hash cell -> http://www.mit.edu/~andoni/LSH/manual.pdf section 3.5.2
  struct lshHash {
    int h1, h2;
    bool operator ==(lshHash const& lsh) const {
      return h1 == lsh.h1 && h2 == lsh.h2;
    }
  };

  // h(x)
  template<typename T, int d, int r>
  struct H {
  public:
    H() : b(rand<uniform_real_distribution<double>, 0, r>()) {
      for(auto& value : a)
        value = rand<normal_distribution<double>, 0, 1>();
    }

    int operator () (array<T, d> const& x) const {
      return static_cast<int>((inner_product(x.begin(), x.end(), a.begin(), 0) + b) / r);
    }
  private:
    array<T, d> a;
    double b;
  };

  // g(x) = [h1(x),h2(x), ....hk(x)]
  template<typename T, int d, int k, int r>
  struct G {
  public:
    G() {
      for(int i = 0; i < k; i++) {
        r1[i] = rand<uniform_int_distribution<int>>();
        r2[i] = rand<uniform_int_distribution<int>>();
      }
    }
    lshHash operator ()(array<T, d> const& x) const {
      lshHash hash = {};
      array<int, k> a;

      for(int i = 0; i < k; i++)
        a[i] = h[i](x);

      hash.h1 = inner_product(a.begin(), a.end(), r1.begin(), 0);
      hash.h2 = inner_product(a.begin(), a.end() ,r2.begin(), 0);
      return hash;
    }
  private:
    array<H<T, d, r>, k> h;
    array<int, k> r1;
    array<int, k> r2;
  };

  template<typename T, int K, int L, int d, int r>
  class pStable {
  public:
    typedef array<T, d> data_type;

    void add(data_type const& val) {
      data.push_back(data_type(val));
      auto& v = data[data.size() - 1];

      // L個のハッシュテーブルに値を格納
      for(int i = 0; i < L; i++)
        hash_tables[i].insert(make_pair(g[i](v), data.size() - 1));
    }

    unordered_set<const data_type*> query(data_type const& query_data) const{
      unordered_set<const data_type*> result;

      for(int i = 0; i < L; i++){
        auto h = g[i](query_data);
        auto range = hash_tables[i].equal_range(h);

        while(range.first != range.second){
          result.insert(&data[range.first->second]);
          ++range.first;
          if(result.size() >= 2 * L) return result;
        }
      }
      return result;
    }
  private:
    array<G<T, d, K, r>, L> g; // Hash-Familiy
    vector<data_type> data;
    array<unordered_multimap<lshHash, int>, L> hash_tables;
  };
}

namespace std {
  // unordered_map使うための部分特殊化
  template<>
  struct hash<LSH::lshHash> {
    size_t operator()(LSH::lshHash const& h) const{
      return h.h1;
    }
  };
}

int main(){
    int const d = 10; // 特徴次元
    int const k = 4; // ハッシュコード長
    int const L = 10;// バケット数
    int const r = 2; // Hash Parameter

    typedef std::array<double, d> data_type;

    LSH::pStable<double, k, L, d, r> hash;

    hash.add(data_type{  1,  2,  3,  4,  5,  6,  7,  8,  9, 10});
    hash.add(data_type{100,100,100,100,100,100,100,100,100,100});
    hash.add(data_type{  1,  2,  5,  4,  5,  6,  7,  8,  9, 10});
    hash.add(data_type{  1,  2,  3,  0,  5,  8,  7,  9,  8, 10});
    hash.add(data_type{  2,  1,  2,  4,  5,  6,  7,  8,  9, 10});
    hash.add(data_type{});

    auto result = hash.query(data_type{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    std::cout << "result:" << std::endl;
    for(auto val : result){
        for(auto v : (*val))
            std::cout << v << ",";
        std::cout << std::endl;
    }
}
    return 0;
}

