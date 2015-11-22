#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
int n, q, qs;
int main()
{
  scanf("%d %d", &n, &qs);
  ++n; // Inclusive

  int c = 0;
  std::vector<bool> is_prime (n, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= sqrt(n+1); i++)
    if (is_prime[i])
    {
      ++c;
      for (int j = i+i; j <= n; j += i) is_prime[j] = false;
    }

  for (int i = sqrt(n+1); i < n; ++i) if (is_prime[i]) ++c;
  
  printf("%d\n", c);
  while (qs--)
  {
    scanf("%d", &q);
    (is_prime[q]) ? printf("1\n") : printf("0\n");
  }
}