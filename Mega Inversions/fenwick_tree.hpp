#ifndef FENWICK_H
#define FENWICK_H
#include <vector>

typedef struct binary_indexed_tree {
  std::vector<long> a;
  long size;

  binary_indexed_tree(long n) {
    size = n;
    a.assign(n, 0);
  }

  // Increment a[i] with v.
  void add(long i, long v = 1) {
    i++;
    for(; i <= size; i += i&-i)
      a[i-1] += v;
  }
  
  // Sum range.
  long sum(long to, long from = 0) {
    return query(to) - query(from);
  }
  
  // Sum a[0..i).
  long query(long i) {
    long s = 0;
    for(; i > 0; i -= i&-i)
      s += a[i-1];
    return s;
  }
} BIT;

#endif /* FENWICK_H */
