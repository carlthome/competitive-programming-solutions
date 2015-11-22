// Author: Carl Thomé

#include <iostream>
#include <string>
#include "search_text.hpp"

int main() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  
  string pattern, text;
  while (getline(cin, pattern) && getline(cin, text)) {
    cerr << "Read:" << endl << pattern << endl << text << endl;
    for (const auto& position :  search_text(pattern, text))
      cout << position << ' ';
    cout << endl;
    cerr << endl;
  }
  
  return 0;
}