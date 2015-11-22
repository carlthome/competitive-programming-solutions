// Author: Carl Thomé

#ifndef PRIME_SIEVE_H
#define PRIME_SIEVE_H
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

// Determine which, and how many, numbers are prime up to the input limit.
pair<int, vector<bool>> identify_primes(long to) {
  ++to; // Inclusive.

  // Sieve of Eratosthenes
  vector<bool> is_prime (to, true);
  is_prime[0] = false;
  is_prime[1] = false;
  for (int i = 2; i <= sqrt(to+1); i++)
    if (is_prime[i])
      for (int j = i*i; j <= to; j += i)
        is_prime[j] = false;

  // Count primes in a linear pass.
  int primes_count = 0;
  for (bool b : is_prime) if (b) ++primes_count;

  return make_pair(primes_count, is_prime);
}

// Get all prime numbers in the input range.
vector<long> get_primes(long from, long to) {
  vector<long> primes;

  vector<bool> is_prime = identify_primes(to).second;
  for (long n = from; n <= to; ++n)
    if (is_prime[n])
      primes.push_back(n);

  return primes;
}

#endif /* PRIME_SIEVE_H */
