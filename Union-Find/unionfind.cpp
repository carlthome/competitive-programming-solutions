// Author: Carl Thomé

#include <cstdio>
#include "disjoint_set.hpp"

using namespace std;
char operation;
int a, b, N, Q;

int main() {
  scanf("%d %d", &N, &Q);

  disjoint_set<int> forest (N);

  while (Q--) {
    scanf("%s %d %d", &operation, &a, &b);
    switch (operation) {
      case '?':
        (forest.same(a, b)) ? printf("yes\n") : printf("no\n");
        break;
      case '=':
        forest.unite(a, b);
        break;
    }
  }

  return 0;
}