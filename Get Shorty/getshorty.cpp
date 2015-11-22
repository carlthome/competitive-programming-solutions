#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
typedef pair<long, double> edge;
typedef vector<vector<edge>> graph;

int main () { 
  long n, m;
  while (cin >> n >> m && !(n == 0 && m == 0)) {

    graph g(n);
    while (m--) {
      long x, y;
      double f;
      cin >> x >> y >> f;

      g[x].push_back(make_pair(y, f));
      g[y].push_back(make_pair(x, f));
    }

    vector<double> max_sizes(n, numeric_limits<double>::min());
    max_sizes[0] = 1;

    auto comparator = [] (const pair<long, double>& c1, const pair<long, double>& c2) {
      return c1.second > c2.second || (c1.second == c2.second && c1.first > c2.first);
    };
    set<pair<long, double>, decltype(comparator)> q(comparator);

    q.insert(make_pair(0, 1));

    while (!q.empty()) {
      auto u = q.begin()->first;
      q.erase(q.begin());
      
      for (auto p : g[u]) {
        auto v = p.first;
        auto fraction = max_sizes[u] * p.second;
        if (fraction > max_sizes[v]) {
          q.erase(make_pair(v, max_sizes[v]));
          q.insert(make_pair(v, fraction));
          max_sizes[v] = fraction;
        }
      }
    }

    cout << fixed << setprecision(4) << max_sizes[n-1] << endl;
  }

  return 0;
}
