// Author: Carl Thomé

#pragma once
#include <cmath>
#include <utility>
#include <functional>
using namespace std;

// Find the greatest common divisor with the Euclidean algorithm.
template <typename T>
T gcd(T a, T b) {
  a = abs(a);
  b = abs(b);
  if (a < b) swap(a, b);
  
  function<T(T,T)> go = [&go] (T a, T b) -> T {
    return (b == 0) ? a : go(b, a % b);
  };

  return go(a, b);
}

// Find the least common multiple.
template <typename T>
T lcm(T a, T b) {
  return a * b / gcd(a, b);
}

// Determine if the numbers a and b are congruent in modulo m.
template <typename T>
T congruent(T a, T b, T m) {
  return a % m == b % m;
}

// Calulate n's inverse in modulo m. Returns -1 iff no inverse exists.
template <typename T>
T inverse(T n, const T& m) {
  T t = 0, t2 = 1;
  T r = m, r2 = n;

  auto update = [] (T& p, T& c, const T& q) { 
    auto swap = c;
    c = p - q * c;
    p = swap;
  };
  
  while (r2) {
    const T q = r / r2;
    update(t, t2, q);
    update(r, r2, q);
  }

  if (r > 1) return -1;
  else return (t < 0) ? t + m : t;
}

// Sum x and y in modulo m.
template <typename T>
T add(T x, T y, const T& m) {
  return (x + y) % m;
}

// Subtract y from x in modulo m.
template <typename T>
T subtract(T x, T y, const T& m) {
  if (y > x) x += m;
  return (x - y) % m;
}

// Calculate product of a and b in modulo m.
template <typename T>
T multiply(T a, T b, const T& m) {
  if (!a || !b) return 0;
  if (a == 1) return b;
  if (b == 1) return a;

  const T res = 2 * multiply(a, b / 2, m) % m; // Divide and conquer!
  bool is_even = !(b&1);
  return is_even ? res : (a % m + res) % m;
}

// Division is defined as multiplying x with y's inverse. Returns -1 iff inverse's non-existant.
template <typename T>
T divide(T x, T y, const T& m) {
  const T yi = inverse(y, m);
  return (yi < 0) ? -1 : multiply(x, yi, m);
}

// Solve the system { x = a1 % m1, x = a2 % m2 }. Returns -1 iff no solution exists.
template <typename T>
T chinese_remainder(T a1, T m1, T a2, T m2) {
  T g = gcd(m1, m2);
  
  // Make sure a solution exists.
  if (!congruent(a1, a2, g)) return -1;
  
  // If m1 and m2 are not coprime use the method of successive substitution.
  if (g != 1) {
    const auto a1c = a1;
    const auto m1c = m1;

    a1 -= a1, a2 -= a1;
    g = gcd(a2, g);
    a1 /= g, a2 /= g, m1 /= g, m2 /= g;
    auto i = inverse(m1, m2);
    a1 *= i, a2 *= i, m1 *= i, m2 *= i;
    const T x = a1c + m1c * a2;
    const T m = m1c * m2;
    
    return (x < 0) ? x + m : x % m;
  } else {
  
    // Calculate x according to the chinese remainder theorem.
    T m = m1*m2;
    const T x = add<T>(
      multiply<T>(a1, multiply<T>(m2, inverse<T>(m2, m1), m), m),
      multiply<T>(a2, multiply<T>(m1, inverse<T>(m1, m2), m), m),
      m
    );

    return (x < 0) ? x + m : x % m;
  }
}