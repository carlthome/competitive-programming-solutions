#include <iostream>
#include <cmath>

using namespace std;
int h, v, x;
int main() {
  cin >> h >> v;
  x = (int) ceil(h/sin(v*0.0174532925));
  cout << x;
  return 0;
}