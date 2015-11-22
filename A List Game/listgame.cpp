#include <iostream>
using namespace std;
int main() {
  int x, k = 0;
  cin >> x;
  
  for (int i = 2; i*i <= x; ++i)
    while (x % i == 0) {
      x /= i;
      ++k;
    }
  if (x != 1) ++k;

  cout << k;
}