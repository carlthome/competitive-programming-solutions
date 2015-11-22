// Author: Carl Thomé

#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H
#include <vector>

template <typename T>
struct disjoint_set {

  private: 
    std::vector<T> parents; // Keep track of node parent.
    std::vector<T> ranks; // Keep track of tree height.
    
  public:

    // Create forest.
    disjoint_set(T n) {
      parents.reserve(n);
      ranks.reserve(n);
      for (T i = 0; i < n; i++) {
        parents.push_back(i);
        ranks.push_back(0);
      }
    }
    
    // Find which subset the element x is in.
    T find(T x) {
      while (x != parents[x]) {
        parents[x] = parents[parents[x]]; // Path compression.
        x = parents[x];
      }
      return x;
    }
    
    // Check if the elements x and y are in the same set.
    bool same(T x, T y) {
      return find(x) == find(y);
    }
    
    // Join the subsets containing elements x and y into a single subset.
    void unite(T x, T y) {
      T root1 = find(x);
      T root2 = find(y);
      
      // Do nothing if elements are already in the same subset.
      if (root1 == root2)
        return;
      
      // Attach smaller tree to larger tree.
      if (ranks[root1] < ranks[root2])
        parents[root1] = root2;
      else if (ranks[root1] > ranks[root2])
        parents[root2] = root1;
      else {
        parents[root2] = root1;
        ++ranks[root1];
      }
    }

};

#endif /* DISJOINT_SET_H */
