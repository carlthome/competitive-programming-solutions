#include <iostream>  
#include <climits>  
#include <cmath>
#define MAX_MAILBOXES 15
#define MAX_CRACKERS 105

int main() {  
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int crackers_needed[MAX_MAILBOXES+1][MAX_CRACKERS+1][MAX_CRACKERS+1];
  for (int safe = 1; safe <= MAX_CRACKERS; safe++)
    for (int lethal = 1; lethal <= MAX_CRACKERS; lethal++)  
      crackers_needed[1][safe][lethal] = safe + (lethal*(lethal + 1) / 2) - (safe*(safe + 1) / 2);

  for (int mailboxes = 2; mailboxes <= MAX_MAILBOXES; mailboxes++)
    for (int lethal = MAX_CRACKERS; lethal >= 1; lethal--)
      for (int safe = lethal; safe >= 1; safe--) {
        int& val = crackers_needed[mailboxes][safe][lethal] = INT_MAX;
        for (int crackers = safe; crackers <= lethal; crackers++)
          val = min(
            val,
            crackers + max(
              crackers_needed[mailboxes-1][safe][crackers-1],
              crackers_needed[mailboxes][crackers+1][lethal]
              )
          );
      }

  int number_of_tests;
  cin >> number_of_tests;
  for (int test = 0; test < number_of_tests; test++) {  

      // Read problem.
      int mailboxes, max_crackers;
      cin >> mailboxes >> max_crackers;
      
      // Solve problem.
      int result = crackers_needed[mailboxes][1][max_crackers];
      
      // Print solution.
      cout << result << endl;
  }  
  return 0;  
}
