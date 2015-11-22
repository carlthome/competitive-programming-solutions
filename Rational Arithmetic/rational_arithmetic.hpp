// Author: Carl Thomé

#ifndef RATIONAL_ARITHMETIC_H
#define RATIONAL_ARITHMETIC_H
#include <cmath>
using namespace std;

// A rational number class.
template <typename T>
class ratio {
  private:
    T n, d; // Numerator and denominator

    // Normalize rational number by removing extraneous factors and minuses.
    inline void normalize() {
    
      // Find the greatest common divisor with the Euclidean algorithm.
      T l = max(abs(n), abs(d)), r = min(abs(n), abs(d));
      while (r) {
        T swap = r;
        r = l % r;
        l = swap;
      }
      T gcd = l;

      // Simplify rational number.
      if (gcd > 1) n = n / gcd, d = d / gcd;
      
      // Always keep denominator positive, and always remove double minuses.
      if (d < 0) n = -n, d = -d;
    }
    
  public:
    ratio(T _n = 0, T _d = 1) : n(_n), d(_d) {};
    
    T numerator() { return n; }
    T denominator() { return d; }
    double to_double() { return (double)n / (double)d; };
    
     // IO
    friend ostream &operator<<(ostream &os, ratio r) {
      os << r.n << " / " << r.d;
      return os;
    }
    friend istream& operator>>(istream& is, ratio& r) {
      T n, d;
      is >> n;
      is.ignore('/', 255);
      is >> d;
      return is;
    }
    
    // Arithmetic
    ratio& operator+=(const ratio& r) {
      n = n*r.d + r.n*d;
      d *= r.d;
      normalize();
      return *this;
    }
    ratio& operator*=(const ratio& r) {
      n *= r.n;
      d *= r.d;
      normalize();
      return *this;
    }
    ratio& operator-=(const ratio& r) { 
      return operator+=(ratio(-r.n, r.d));
    }
    ratio& operator/=(const ratio& r) {
      return operator*=(ratio(r.d, r.n));
    }
    friend ratio operator+(ratio l, const ratio& r) { return l += r; }
    friend ratio operator-(ratio l, const ratio& r) { return l -= r; }
    friend ratio operator*(ratio l, const ratio& r) { return l *= r; }
    friend ratio operator/(ratio l, const ratio& r) { return l /= r; }

    // Comparisons
    friend bool operator==(const ratio& l, const ratio& r) { return (l-r).n == 0; }
    friend bool operator!=(const ratio& l, const ratio& r) { return !operator==(l,r); }
    friend bool operator< (const ratio& l, const ratio& r) { return (l-r).n < 0; }
    friend bool operator> (const ratio& l, const ratio& r) { return operator< (r,l); }
    friend bool operator<=(const ratio& l, const ratio& r) { return !operator> (l,r); }
    friend bool operator>=(const ratio& l, const ratio& r) { return !operator< (l,r); }
};

#endif /* RATIONAL_ARITHMETIC_H */
