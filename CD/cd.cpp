#include <cstdio>
#include <unordered_set>

using namespace std;

int N, M, cd, cd_count = 0;
unordered_set<int> cds;
int main() {

  while (scanf("%d %d", &N, &M) == 2) {
    if (N == 0 && M == 0)
      break;

    int iter = N+M;
    while (iter--) {
      scanf("%d", &cd);
      if (!cds.insert(cd).second)
        ++cd_count;
    }

    printf("%d\n", cd_count);
  }

  return 0;
}