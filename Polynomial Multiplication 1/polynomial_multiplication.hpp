// Author: Carl Thomé

#ifndef POLYNOMIAL_MULTIPLICATION_H
#define POLYNOMIAL_MULTIPLICATION_H

#include <vector>
#include <cmath>
using namespace std;
typedef vector<int> polynomial;

int get_degree(polynomial p) {
  return p.size()-1;
}

polynomial multiply(polynomial p1, polynomial p2) {
  polynomial product (p1.size()+p2.size(), 0);

  while (p1.size() < p2.size()) p1.push_back(0);
  while (p2.size() < p1.size()) p2.push_back(0);  
  
  for (int i = 0; i < p1.size(); ++i)
    for (int j = 0; j < p2.size(); ++j)
      product[i+j] += p1[i]*p2[j];
   
  while (product.back() == 0) product.pop_back();
  
  return product;
}

#endif /* POLYNOMIAL_MULTIPLICATION_H */
