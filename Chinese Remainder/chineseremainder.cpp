// Author: Carl Thomé

#include <iostream>
#include <cassert>
#include "modular_arithmetic.hpp"

int main() {	
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
 
  int T;
  cin >> T;
  assert(1 <= T && T <= 1000);
  while (T--) {
    // Read problem
    long long T, a, n, b, m;
    cin >> a >> n >> b >> m;
    assert(1 <= n && n <= 1e9);
    assert(1 <= m && m <= 1e9);
    assert(0 <= a && a <= n);
    assert(0 <= b && b <= m);
    
    // Solve
    auto x = chinese_remainder<long long>(a, n, b, m);
    auto K = n*m;
    assert(x != -1);
    
    // Print solution
    cout << x << ' ' << K << endl;
  }
  
  return 0;
}