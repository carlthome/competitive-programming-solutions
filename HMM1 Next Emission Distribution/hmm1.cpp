#include <iostream>
#include "hmm.hpp"
using namespace std;

int main()
{
  int rows, columns;
  
  cin >> rows >> columns;
  matrix A = initialize_matrix(rows, columns);
  for (int y = 0; y < rows; ++y) for (int x = 0; x < columns; ++x) cin >> A[y][x];
  
  cin >> rows >> columns;
  matrix B = initialize_matrix(rows, columns);
  for (int y = 0; y < rows; ++y) for (int x = 0; x < columns; ++x) cin >> B[y][x];
  
  cin >> rows >> columns;
  matrix pi = initialize_matrix(1, columns);
  for (int x = 0; x < columns; ++x) cin >> pi[0][x];
  
  auto model = hmm(A, B, pi);

  auto res = model.next_emission_distribution();

  cout << 1 << ' ' << res[0].size();
  for (auto e : res[0]) cout << ' ' << e;
  cout << endl;

  return 0;
}
