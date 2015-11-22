#include <iostream>
#include <vector>
#include <cmath>
#define MAX_DISTANCE 10000
#define MAX_PRICE 2000

using namespace std;
int main() {

  long distance;
  cin >> distance;
  
  vector<long> m;
  m.insert(m.end(), 100, 0);
  m.insert(m.end(), distance, MAX_PRICE+1);

  long d, p;
  while(cin >> d >> p)
    for(int i = 0; i < 200; ++i)
      if (d+i < distance+100)
        m[d+i] = min(m[d+i], p);

  long s = 0;
  for (auto n : m) {
    s += n;

    if (n == MAX_PRICE+1) {
      cout << "Impossible";
      return 0;
    }
  }
  
  cout << s;
  return 0;
}
