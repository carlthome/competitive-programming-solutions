// Author: Carl Thomé

#include <iostream>
#include "polynomial_multiplication.hpp"

int main() {	
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int T, d, c;
  cin >> T;
  while (T--) {
    polynomial p1, p2;
    
    cin >> d;
    ++d;
    while (d--) {
      cin >> c;
      p1.push_back(c);
    }

    cin >> d;
    ++d;
    while (d--) {
      cin >> c;
      p2.push_back(c);
    }

    polynomial product = multiply(p1, p2);
    cout << get_degree(product) << '\n';
    for (int i = 0; i < product.size(); ++i) {
      cout << product[i];
      i != product.size()-1 ? cout << ' ' : cout << '\n'; 
    }
  }
  
  return 0;
}