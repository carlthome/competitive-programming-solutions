#include <iostream>
using namespace std;

long count(long n) {
  long c = 1, l = n, r = 0, e = 1, i = 0;
  while (l) {
    auto d = l % 10;
    l /= 10;

    c += (d) ? l * e : (l-1) * e + r + 1;

    r = d * e + r;
    e *= 10;
    ++i;
  }
  return c;
}

int main () {
  long from, to;
  while (cin >> from >> to && from >= 0) {
    long zeroes = count(to) - count(from);

    do {
      if (from % 10 == 0) ++zeroes;
    } while (from/=10);
    
    cout << zeroes << endl;
  }
}
