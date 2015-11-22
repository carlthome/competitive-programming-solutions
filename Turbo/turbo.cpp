#include <iostream>
#include <cstring>
#define MAX_N 100000
 
using namespace std;
 
typedef struct binary_indexed_tree {
  int a[MAX_N+1];
  int n;
 
  binary_indexed_tree(int _n) : n(_n) {
    memset(a, 0, sizeof a);
  }
  
  int query(int X) {
    int ret = 0;
    for(int x = X; x > 0; x -= x&-x)
      ret += a[x];
    return ret;
  }
 
  int sum(int from, int to) {
    return query(to) - query(from-1);
  }
 
  void add(int X, int val) {
    for(int x = X; x <= n; x += x&-x)
      a[x] += val;
  }
 
} fenwick;
 
int main() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
 
  int n, ns[MAX_N+1], is[MAX_N+1];
  cin >> n;
  fenwick tree(n);
  for(int i = 1; i <= n; ++i) {
    cin >> ns[i];
    is[ns[i]] = i;
    tree.add(i, 1);
  }
 
  int l = 1, r = n;
  for( int i = 1; i <= n; ++i ) {
  //while (l != r) {
    if( i%2 == 1 ) {
      tree.add(is[l], -1);
      cout << tree.sum(1, is[l]) << endl;
      ++l;
    } else {
      tree.add(is[r], -1);
      cout << tree.sum(is[r], n) << endl;
      --r;
    }
  }
 
  return 0;
}