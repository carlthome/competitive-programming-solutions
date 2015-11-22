#include <stdio.h>

int main()
{
  long long unsigned int a, b, d;
  while (scanf("%llu %llu", &a, &b) == 2)
  {
    if (a > b)
      d = a - b;
    else
      d = b - a;
    printf("%llu\n", d);
  }
  return 0;
}