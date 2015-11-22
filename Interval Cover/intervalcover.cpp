// Author: Carl Thomé

#include <iostream>
#include <vector>
#include "interval_cover.hpp"

int main() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  // Read problem.
  double A, B, n;
  while (cin >> A >> B >> n) {
    interval goal = interval(A, B, n+1);
    vector<interval> domain;
    for (int i = 0; i < n; i++) {
      double a, b;
      cin >> a >> b;
      domain.push_back(interval(a, b, i));
    }

    // Solve.
    vector<int> indices = cover(goal, domain);

    // Print solution in ascending order.
    sort(indices.begin(), indices.end());
    if (indices.size() == 0)
      cout << "impossible" << endl;
    else {
      cout << indices.size() << endl;
      for (int i = 0; i < indices.size(); i++)
        (i < indices.size() - 1) ? cout << indices[i] << ' ' : cout << indices[i] << endl;
    }
  }

	return 0;
}
