#include <iostream>
#include <string>

int main()
{
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  
  int tc;
  cin >> tc;
  while (tc--) {
    cerr << "Test: " << tc+1 << endl;
    int scrolled = 0;
    
    int k, w;
    cin >> k >> w;
    cerr << "Sign: " << k << endl;
    cerr << "Words: " << w << endl;
    cin.ignore(255, '\n');

    string w1 = "", w2 = "";
    for (int i = 0; i < w; i++) {
      getline(cin, w1);
      cerr << "Word 1: " << w1 << ", Word 2: " << w2 << endl;

      if (w2 == "")
        scrolled = k;
      else {
        int same = 0;
        for (int i = 0; i < k; i++) {
          if (w2.substr(i, k-i) == w1.substr(0, k-i)) {
            same = k-i;
            cerr << w2.substr(i, k-i) << " = " << w1.substr(0, k-i) << endl;
            cerr << "Same: " << same << endl;
            break;
          }
        }
        scrolled += k - same;
      }

      w2 = w1;
    }

    cout << scrolled << endl;
    cerr << endl;
  }

  
  return 0;
}