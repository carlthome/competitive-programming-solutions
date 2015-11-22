#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>
#include <queue>
#include "disjoint_set.hpp"

using namespace std;
typedef pair<int, int> edge;
double m[1001][1001];

int main() {	
  ios::sync_with_stdio(false);
  cin.tie(NULL);
 
  // Solve (several test cases).
  int tc;
  cin >> tc;
  while (tc--) {
    int n;
    
    // Number of freckles.
    cin >> n;
    assert(0 < n && n <= 1000);
    
    // Read freckle positions in the plane.
    vector<pair<double, double>> coordinates;
    for (int i = 0; i < n; ++i) {
      double x, y;
      cin >> x >> y;
      coordinates.push_back(make_pair(x, y));
    }
   
    // Calculate distances between freckles (a complete graph).
    priority_queue<pair<double, edge>> q;
    for (int i = 0; i < n; ++i) {
      const auto& x2 = coordinates[i].first;
      const auto& y2 = coordinates[i].second;
      for (int j = 0; j < n; ++j) {
        const auto& x1 = coordinates[j].first;
        const auto& y1 = coordinates[j].second;
        double d = sqrt(pow((x2-x1),2) + pow((y2-y1),2));
        edge e = make_pair(i, j);
        m[i][j] = d;
        q.push(make_pair(-d, e));
      }
    }

    // Calculate how much ink is needed by finding a minimal spanning tree (Kruskal's algorithm).
    double distance = 0;
    vector<edge> A;
    disjoint_set<int> sets(n);
    while (!q.empty()) {
      const auto& e = q.top().second;
      const int u = e.first;
      const int v = e.second;
      if (!sets.same(u, v)) {
        distance += m[u][v];
        A.push_back(e);
        sets.unite(u, v);
      }
      q.pop();
    }
  
    // Print results.
    cout << fixed << setprecision(2) << distance << endl;
  }

  return 0;
}
