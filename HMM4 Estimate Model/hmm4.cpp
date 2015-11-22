#include <iostream>
#include "hmm.hpp"
using namespace std;

int main()
{
  int rows, columns;

  cin >> rows >> columns;
  matrix A = initialize_matrix(rows, columns);
  for (int x = 0; x < rows; ++x) for (int y = 0; y < columns; ++y) cin >> A[x][y];
  
  cin >> rows >> columns;
  matrix B = initialize_matrix(rows, columns);
  for (int x = 0; x < rows; ++x) for (int y = 0; y < columns; ++y) cin >> B[x][y];
  
  cin >> rows >> columns;
  matrix pi = initialize_matrix(1, columns);
  for (int x = 0; x < columns; ++x) cin >> pi[0][x];
  
  auto model = hmm(A, B, pi);
  
  int observations;
  cin >> observations;
  for (int i = 0; i < observations; ++i)
  {
    int o;
    cin >> o;
    model.O.push_back(o);
  }
  
  model.estimate_model(35);
  
  A = model.A;
  B = model.B;

  cout << A.size() << ' ' << A[0].size();
  for (auto v : A) for (auto e : v) cout << ' ' << e;
  cout << endl; 
  
  cout << B.size() << ' ' << B[0].size();
  for (auto v : B) for (auto e : v) cout << ' ' << e;
  cout << endl;

  return 0;
}

