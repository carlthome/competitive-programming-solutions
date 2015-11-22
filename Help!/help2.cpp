#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

inline bool is_pattern_placeholder(std::string s) {
  return (s[0] == '<' && s[s.size() - 1] == '>') ? true : false;
}

int main() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  
  int number_of_tests;
  cin >> number_of_tests;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  for (int i = 0; i < number_of_tests; i++) {
  
    // Read patterns from stdin as lines of text.
    string line1, line2;
    getline(cin, line1);
    getline(cin, line2);

    // Parse lines into words.
    vector<string> pattern1, pattern2;
    istringstream iss1(line1);
    copy(istream_iterator<string>(iss1),
         istream_iterator<string>(),
         back_inserter<vector<string> >(pattern1));
    istringstream iss2(line2);
    copy(istream_iterator<string>(iss2),
         istream_iterator<string>(),
         back_inserter<vector<string> >(pattern2));

    // Construct phrase from the pattern pair.
    filter:
    for (int i = 0; i < pattern1.size(); i++) {
      const auto& word1 = pattern1[i];
      const auto& word2 = pattern2[i];

      if (is_pattern_placeholder(word1) && !is_pattern_placeholder(word2)) {
        const auto placeholder = word1;
        const auto phrase_word = word2;
        auto& pattern = pattern1;
                  
        for (string& word : pattern)
          if (word == placeholder)
            word = phrase_word;
        goto filter;
      } else if (!is_pattern_placeholder(word1) && is_pattern_placeholder(word2)) {
        const auto placeholder = word2;
        const auto phrase_word = word1;
        auto& pattern = pattern2;
        
        for (string& word : pattern)
          if (word == placeholder)
            word = phrase_word;
        goto filter;
      } else if (is_pattern_placeholder(word1) && is_pattern_placeholder(word2)) {
        continue;
      } else if (word1 == word2) {
        continue;
      } else { // Fail!
        cout << '-' << endl;
        goto next_test;
      }
    }

    // Print phrase.
    for (int i = 0; i < pattern1.size(); i++) {
      const auto& word1 = pattern1[i];
      const auto& word2 = pattern2[i];

      if (is_pattern_placeholder(word1) && is_pattern_placeholder(word2))
        cout << "whatever" << ' ';
      else if (!is_pattern_placeholder(word1))
        cout << word1 << ' ';
      else if (!is_pattern_placeholder(word2))
        cout << word2 << ' ';
    }
    cout << endl;
    
    next_test:
    continue;
  }
  
  return 0;
}