#include <iostream>
#include <cstring>
#include <cmath>
#include <climits>
#define COKE_PRICE 8
#define MAX_COKES 151
#define MAX_FIVES 151
#define MAX_TENS 51

int m[MAX_COKES][MAX_FIVES][MAX_TENS];
int total_cokes, total_money;

int solve(int cokes, int fives, int tens) {
  using namespace std;
  
  int& coins = m[cokes][fives][tens];

  if (cokes == 0)
    return coins = 0;

  if (coins == -1) { // First time seeing sub-problem so it needs to be calculated.
    coins = INT_MAX;

    int ones = total_money - 8 * (total_cokes-cokes) - 5*fives - 10*tens;

    if (ones >= 8)
      coins = min(coins, 8 + solve(cokes-1, fives, tens));
      
    if (fives >= 1 && ones >= 3)
      coins = min(coins, 4 + solve(cokes-1, fives-1, tens));
      
    if (tens >= 1 && ones >= 3)
      coins = min(coins, 4 + solve(cokes-1, fives+1, tens-1));
      
    if (fives >= 2)
      coins = min(coins, 2 + solve(cokes-1, fives-2, tens));

    if (tens >= 1)
      coins = min(coins, 1 + solve(cokes-1, fives, tens-1));
  }
  return coins;
}

int main() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  memset(m, -1, sizeof(m));
  
  int number_of_tests;
  cin >> number_of_tests;
  for (int i = 0; i < number_of_tests; i++) {
    int cokes, ones, fives, tens;
    cin >> cokes >> ones >> fives >> tens; 
    total_cokes = cokes;
    total_money = 1*ones + 5*fives + 10*tens;
    int coins_used = solve(cokes, fives, tens);
    cout << coins_used << endl;
  }
  
  return 0;
}