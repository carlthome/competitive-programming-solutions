#include <iostream>
#include <cassert>
#include "fenwick_tree.hpp"
#define MAX_N 100000

using namespace std;
int main() {

  // Read problem.
  long n;
  cin >> n;
  assert(1 <= n && n <= MAX_N);

  vector<long> ns (n);
  for (long i = 0; i < n; ++i) {
    cin >> ns[i];
    assert(1 <= ns[i] && ns[i] <= n);
  }

  // Solve.
  long inversions_count = 0;
  BIT occurences(n+1);
  BIT inversions(n+1);

  // Go through the numbers array from left to right.
  for (const auto& a : ns) {

    // Note that number a has been found.
    occurences.add(a);
    
    // Count all larger numbers than a, to the left of a.
    long larger = occurences.sum(n+1, a+1); // Inclusive.
    
    // The number of inversions required is the count of larger numbers to the left.
    inversions.add(a, larger);
    
    // Count the number of inversions that needs to be done.
    long j = inversions.sum(n+1, a+1); // Inclusive.
    
    // Sum all done inversions.
    inversions_count += j;
  }

  // Print solution.
  cout << inversions_count << endl;

  return 0;
}
