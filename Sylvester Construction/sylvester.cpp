#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
int main() {    
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  
  ll tc;
  cin >> tc;
  while (tc--) {
    ll n, x, y, w, h;
    cin >> n >> x >> y >> w >> h;
    
    ll e = 0;
    while (n > 1) n /= 2, ++e;
    
    for (ll j = y; j < y+h; ++j) {
      bool needs_space = false;
      for (ll i = x; i < x+w; ++i) {
        if (needs_space) {
          cout << ' ';
        }
        needs_space = true;
        bool neg = false;
        for (ll k = 0; k < e; ++k) {
          neg ^= ((j >> k) & 1) & ((i >> k) & 1);
        }
        neg ? cout << -1 : cout << 1;
      }
      cout << endl;
    }
    cout << endl;
  }
  
  return 0;
}