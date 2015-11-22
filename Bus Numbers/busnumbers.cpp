#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  
  int numberOfBuses;
  cin >> numberOfBuses;
  
  vector<int> buses;
  buses.reserve(numberOfBuses);
  
  int busNumber;
  while (cin >> busNumber)
    buses.push_back(busNumber);
    
  sort(buses.begin(), buses.end());

  for (auto it = buses.begin(); it != buses.end(); it++) {

    int bus = *it;      
    int nextBus = *it;
    int skip = 0;
    while (*next(it) - *it == 1) {
      advance(it, 1);
      nextBus = *it;
      ++skip;
    }
    
    if (skip > 1)
      cout << bus << '-' << nextBus << ' ';
    else if (skip == 1)
      cout << bus << ' ' << nextBus << ' ';
    else // skip == 0
      cout << bus << ' ';
  }
  
  return 0;
}
