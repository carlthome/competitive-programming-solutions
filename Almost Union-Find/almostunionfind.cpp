#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#define MAX_M 100000
//#define MAX_N 100000 TODO Read problem instructions correctly?
using namespace std;

int main() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int elements, commands, command, p, q;
  while (cin >> elements >> commands) {

    vector<set<int>> sets (elements+1);
    vector<int> lookup (elements+1);
    for (int i = 1; i <= elements; ++i) {
      sets[i].insert(i);
      lookup[i] = i;
    }

    while (commands--) {
      cin >> command;
      if (command == 1) { // Union sets containing p and q.
        cin >> p >> q;
        auto& s1 = sets[lookup[p]];
        auto& s2 = sets[lookup[q]];
        if (s1 != s2) {
          for (const auto& n : s2) {
            s1.insert(n);
            lookup[n] = lookup[p];
          }
          s2.clear();
        }
      } else if (command == 2) { // Move element p to set containing q.
        cin >> p >> q;
        auto& s1 = sets[lookup[p]];
        auto& s2 = sets[lookup[q]];
        if (s1 != s2) {
          s1.erase(p);
          s2.insert(p);
          lookup[p] = lookup[q];
        }
      } else if (command == 3) { // Print size and sum of set containing p.
        cin >> p;
        auto& s = sets[lookup[p]];
        int sum = 0;
        for (const auto& n : s)
          sum += n;
        cout << s.size() << ' ' << sum << endl;
      }
    }

  }

  return 0;
}