#include <iostream>

typedef unsigned long long int ull;
using namespace std;
int main() {
  ull N, b;
  cin >> N >> b;
  (ull(1) << (b+1) > N) ? cout << "yes" : cout << "no";
  return 0;
}