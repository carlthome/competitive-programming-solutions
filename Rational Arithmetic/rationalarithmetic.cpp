// Author: Carl Thomé

#include <iostream>
#include <cassert>
#include "rational_arithmetic.hpp"
#define UPPER_BOUND 1000000000
#define LOWER_BOUND -1000000000

using namespace std;
typedef long long ll;
int main() {
  ll tc, x1, y1, x2, y2;
  char op;
  cin >> tc;
  while (tc--) {
    cin >> x1 >> y1 >> op >> x2 >> y2;
    assert(LOWER_BOUND <= x1 && x1 < UPPER_BOUND);
    assert(LOWER_BOUND <= y1 && y1 < UPPER_BOUND);
    assert(LOWER_BOUND <= x2 && x2 < UPPER_BOUND);
    assert(LOWER_BOUND <= y2 && y2 < UPPER_BOUND);
    
    ratio<ll> r1 (x1, y1);
    ratio<ll> r2 (x2, y2);

    switch (op) {
      case '+': cout << r1 + r2; break;
      case '-': cout << r1 - r2; break;
      case '*': cout << r1 * r2; break;
      case '/': cout << r1 / r2; break;
    }
    cout << endl;
  }

  return 0;
}