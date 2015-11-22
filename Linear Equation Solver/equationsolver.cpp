// Author: Carl Thomé

#include <iostream>
#include "linear_equation_solver.hpp"

int main() {	
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
 
  int n;
  while (cin >> n && n != 0) {
  
    matrix A (n, vector<long double> (n));
    vector<long double> b (n);
    
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> A[i][j];
    for (int i = 0; i < n; ++i) cin >> b[i];
    
    auto p = solve_linear_system(A, b);
    const auto& x = p.first;
    const auto& r = p.second;

    switch (r) {
      case ONE_SOLUTION: for (auto e : x) cout << e << ' '; break;
      case MULTIPLE_SOLUTIONS: cout << "multiple"; break;
      case NO_SOLUTIONS: cout << "inconsistent"; break;
    }
    cout << endl;
  }
  
  return 0;
}