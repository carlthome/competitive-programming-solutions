#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int r, k;
    cin >> r >> k;

    for (int i = 0; i < r; ++i) {
     for (int j = 0; j < k; ++j) {
        auto n = min(j+1, min(k - j, min(r - i, i+1)));
        n > 9 ? cout << '.' : cout << n;
     }
     cout << '\n';
    }
}
