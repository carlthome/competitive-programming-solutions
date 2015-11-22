#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class trie {
  
  private:
    struct node {
      std::unordered_map<char, node*> children;
    };
  
  node root;
  
  public:
    bool insert(std::string w) {
      bool consistent = true;
      node* np = &root;
      for (char& c : w) {
        if (np->children.find(c) == np->children.end()) {
          node* n = new node();
          np->children[c] = n;
        }
        
        if (np->children.find('.') != np->children.end())
          consistent = false;
        np = np->children[c];        
      }

      node* n = new node();
      np->children['.'] = n;
      
      return consistent;
    }
};

int main() {
  using namespace std;
  int tc;
  cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    cin.ignore(255, '\n');
    vector<string> ws (n);
    for (int i = 0; i < n; ++i)
      cin >> ws[i];

    sort(ws.begin(), ws.end());

    bool consistent = true;
    trie t;
    for (int i = 0; i < n; ++i)
      if (!t.insert(ws[i])) {
        consistent = false;
        break;
      }

    (consistent) ? cout << "YES\n" : cout << "NO\n";
  }
  
  return 0;
}