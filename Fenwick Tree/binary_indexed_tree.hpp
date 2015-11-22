// Author: Carl Thomé

#ifndef BINARY_INDEXED_TREE_H
#define BINARY_INDEXED_TREE_H
#include <vector>

template <typename T>
struct binary_indexed_tree {
  std::vector<T> a;

  binary_indexed_tree(size_t n) {
    a.assign(n, T());
  }

  // Increment a[i] with v.
  void add(size_t i, T v = T(1)) {
    i++;
    for(; i <= a.size(); i += i&-i)
      a[i-1] += v;
  }
  
  // Sum range a[from..to).
  T sum(size_t to, size_t from = 0) {
    return query(to) - query(from);
  }
  
  // Sum a[0..i).
  T query(size_t i) {
    T s = T();
    for(; i > 0; i -= i&-i)
      s += a[i-1];
    return s;
  }
};

#endif /* BINARY_INDEXED_TREE_H */
