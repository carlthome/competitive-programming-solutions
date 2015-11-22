#include <iostream>
#include <cmath>
#include <random>
#include <vector>

using namespace std;
typedef long long ll;

ll mod_exponent(ll base, ll exponent, ll modulo) { 
  ll result = 1;
  while (exponent > 0) {
    if (exponent % 2 == 1) result = (result * base) % modulo;
    exponent = exponent >> 1;
    base = (base * base) % modulo;
  }
  return result;
}

const ll k = 100;
default_random_engine generator;
bool is_prime(ll n) {
  if (n == 1) return false;
  if (n == 2) return true;
  if (n == 3) return true;
  if (n % 2 == 0) return false;
  
  uniform_int_distribution<ll> distribution(2, n-2);
  
  ll d = n-1;
  ll s = 0;
  while (d % 2 == 0) d /= 2, ++s;
  
  for (ll i = 0; i < k; ++i) {
    ll a = distribution(generator);
    auto x = mod_exponent(a, d, n);
    
    if (x == 1 || x == n-1) continue;
    
    for (ll j = 0; j < s; ++j) {
      x = mod_exponent(x, 2, n);
      if (x == 1) return false;
      if (x == n-1) goto next;
    }
    return false;
    next: continue;
  }
  
  return true;
}

int main() {    
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  ll p, a;
  while(cin >> p >> a && (p != 0 && a != 0)) {
    auto r = mod_exponent(a, p, p);
    auto b = is_prime(p);
    (r == a && !b) ? cout << "yes\n" : cout << "no\n";
  }
  
  return 0;
}