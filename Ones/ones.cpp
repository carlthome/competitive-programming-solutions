#include <iostream>
using namespace std;
typedef long long unsigned int t;

t count_ones(t n) {
  t ones_count = 1;
  t remainder = 1;
  t ones = 1;
  while (remainder != 0) {
    if (ones < n) {
      ++ones_count;
      ones = ones * 10 + 1; 
    }
    remainder = ones % n;
    ones = remainder;
  }
  return ones_count;
}

int main() {
  t n;
  while (cin >> n) cout << count_ones(n) << endl;
  return 0;
}