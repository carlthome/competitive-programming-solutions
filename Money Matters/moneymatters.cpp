#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

typedef unsigned int person;
typedef person vertex;
typedef int debt;

struct graph {
  vector<vector<vertex>> neighbors;
  graph(int n) {
    neighbors.resize(n);
  }
};

int main() {	
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
 
  // Solve.
  int n, m;
  cin >> n >> m;
  assert(2 <= n <= 10000); // Friends count.
  assert(0 <= m <= 50000); // Remaining friends count.
  
  unordered_map<person, debt> debts;
  graph g (n);
  
  // Read persons and debts.
  for (unsigned int person = 0; person < n; ++person)
    cin >> debts[person];
  
  // Read graph.
  for (unsigned int friendship = 0; friendship < m; ++friendship) {
    unsigned int x, y; // Persons x and y are still friends.
    cin >> x >> y;
    assert(0 <= x && x < y && y <= n-1);
    g.neighbors[x].push_back(y);
    g.neighbors[y].push_back(x);
  }
  
  // BFS. 
  // Sum vertice values per component. If sum is zero for all components: debts can be paid out.  
  queue<vertex> s;
  int components_count = 1;
  s.push(0);
  vector<bool> visited (n, false);

  bfs:
  long sum = 0;
  while (!s.empty()) {
    auto v = s.front(); s.pop();
    for (auto w : g.neighbors[v]) {
      if (visited[w]) continue;
      else visited[w] = true;
      sum += debts[w];
      s.push(w);
    }
  }

  if (sum > 0) {
    cout << "IMPOSSIBLE";
    return 0;
  }
  
  // Make sure all graph components have been visited.
  for (vertex v = 0; v < n; ++v) {
    if (!visited[v]) {
      s.push(v);
      ++components_count;
      goto bfs;
    }
  }

  cout << "POSSIBLE";
  return 0;
}