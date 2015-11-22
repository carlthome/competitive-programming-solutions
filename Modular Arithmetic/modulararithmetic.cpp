// Author: Carl Thomé

#include <iostream>
#include <cassert>
#include "modular_arithmetic.hpp"

int main() {
  using namespace std;
  typedef long long ll;
  ll n, t, x, y;
  char op;

  while (cin >> n >> t && !(n == 0 && t == 0)) {
    assert(1 <= n && n <= 10e18);
    assert(0 <= t && t <= 100);
       
    while (t--) {
      cin >> x >> op >> y;
      assert(0 <= x && x < n);
      assert(0 <= y && y < n);

      switch (op) {
        case '+': cout << add<ll>(x, y, n); break;
        case '-': cout << subtract<ll>(x, y, n); break;
        case '*': cout << multiply<ll>(x, y, n); break;
        case '/': cout << divide<ll>(x, y, n); break;
      }
      cout << endl;
    }
  }

  return 0;
}