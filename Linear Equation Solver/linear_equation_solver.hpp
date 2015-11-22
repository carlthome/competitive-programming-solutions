// Author: Carl Thomé

#ifndef LINEAR_EQUATION_SOLVER_H
#define LINEAR_EQUATION_SOLVER_H
#include <iostream>
#include <utility>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef vector<vector<long double>> matrix;
enum result { ONE_SOLUTION, MULTIPLE_SOLUTIONS, NO_SOLUTIONS};

// Solve the linear system of equations Ax=b. A has to be square matrix.
pair<vector<long double>, result> solve_linear_system(matrix A, vector<long double> b) {
  vector<long double> x (b.size());
  const auto n = A.size();

  // Swap rows so the diagonal element is as large as possible.
  for (int k = 0; k < n; ++k) { // For each diagonal element
    auto max = A[k][k];
    auto row = k;
    for (int i = k+1; i < n; ++i) {
      auto next = fabs(A[i][k]);
      if (next > max) {
        max = next;
        row = i;
      }
    }
    swap(A[k], A[row]);
    swap(b[k], b[row]);
  }
  
  // Reduce system with Gauss elimination.
  for (int k = 0; k < n; ++k) {

    // Determine if the linear system is solvable.
    if (A[k][k] == 0) {
      for (int i = 0; i < n; ++i) {
        bool zero_row = true;
        for (int j = 0; j < n; ++j) { 
          if (A[i][j] != 0) {
            zero_row = false;
            break;
          }
        }
        if (zero_row && b[i] != 0) return make_pair(x, NO_SOLUTIONS);
      }
      return make_pair(x, MULTIPLE_SOLUTIONS);
    }

    // Gaussian elimination
    for (int i = k+1; i < n; ++i) {
      const auto q = A[i][k] / A[k][k];
      for (int j = k; j < n; ++j) A[i][j] -= q * A[k][j];
      b[i] -= q*b[k];
      A[i][k] = 0;
    }
  }

  // Backward sweep
  for (int i = n-1; i >= 0; --i) {
    auto d = b[i];
    for (int j = n-1; j > i; --j) d -= A[i][j] * x[j];
    x[i] = d / A[i][i];
  }

  return make_pair(x, ONE_SOLUTION);
}

#endif /* LINEAR_EQUATION_SOLVER_H */
