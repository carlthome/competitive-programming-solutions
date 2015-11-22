// Author: Carl Thomé

#include <cstdio>
#include "binary_indexed_tree.hpp"

long N, Q, i, delta;
char operation;
int main() {
  scanf("%ld %ld", &N, &Q);
  
  binary_indexed_tree<long> fenwick (N);
  
  while (Q--) {
    scanf("%s", &operation);
    switch (operation) {
      case '+':
        scanf("%ld %ld", &i, &delta);
        fenwick.add(i, delta);
        break;
      case '?':
        scanf("%ld", &i);
        printf("%ld\n", fenwick.sum(i));
        break;
    }
  }
  
  return 0;
}