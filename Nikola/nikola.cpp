#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#define MAX_SQUARES 1000
#define INF 100000
using namespace std;

int m[MAX_SQUARES+1][MAX_SQUARES+1];
vector<int> fees;
int solve(int square, int step) {
  if (square < 0 || square > fees.size() - 1) return INF;
  
  auto& v = m[square][step];
  
  if (square == fees.size()-1) return fees[square] - fees[0];

  if (v == -1) { 
    int c1 = fees[square] + solve(square+step+1, step+1);
    int c2 = (step != 0) ? fees[square] + solve(square-step, step) : INF;
    v = min(c1, c2);
  }
  
  return v;
}

int main() {	
  ios::sync_with_stdio(false);
  cin.tie(NULL);
 
  // Read problem.
  int N;
  cin >> N;
  assert(2 <= N && N <= 1000);
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) m[i][j] = -1;
  fees.resize(N);
  for (int i = 0; i < N; ++i) {
    cin >> fees[i];
    assert(0 < fees[i] && fees[i] < 500);
  }

  // Solve.
  int smallest_total_cost = solve(0, 0);  
    
  // Print solution.
  cout << smallest_total_cost;
  
  return 0;
}