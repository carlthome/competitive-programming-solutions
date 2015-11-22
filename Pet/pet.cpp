#include <iostream>
#include <vector>
#define CONTESTANTS 5

int main()
{
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  
  int winner, winners_score = 0;
  for (int contestant = 1; contestant <= CONTESTANTS; contestant++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int score = a + b + c + d;
    
    if (score > winners_score) {
      winner = contestant;
      winners_score = score;
    }
  }
  
  cout << winner << ' ' << winners_score;
  
  return 0;
}