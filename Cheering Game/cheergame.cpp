#include <iostream>
#define MATCH_LENGTH 90
#define HALF_TIME 45
#define MAX_CHEERLEADERS 20
#define MAX_SPY_REPORTS 1000

using namespace std;

typedef struct score {
  int sportify, spoilify;
  score(int _sportify = -1, int _spoilify = -1) : sportify(_sportify), spoilify(_spoilify) {}
  
  bool is_memoized() { 
    return (sportify != -1 && spoilify != -1);
  }

  bool operator>(const score& b) const {
    int d1 = this->sportify - this->spoilify;
    int d2 = b.sportify - b.spoilify;
          
    if (d1 != d2)
      return (d1 > d2);
    else
      return (this->sportify > b.sportify);
  }
  
} score;

int cheerleaders, cheer_length, spy_reports;
int spoilify_cheers[MAX_SPY_REPORTS] = {0};
score scores[MATCH_LENGTH+1][MATCH_LENGTH*MAX_CHEERLEADERS+1][10];

score solve(int time, int cheer_sum, int state) {

  // No team can score points before the game has started.
  if (time == 0) 
    return score(0,0);

  // A cheer can't produce scores over half-time.
  if (time == HALF_TIME)
    state = 0;

  score &now = scores[time][cheer_sum][state+4];

  if (now.is_memoized()) 
    return now;
  else { 

    // Try all amounts of cheer.
    for (int cheer = 0; cheer <= min(cheer_sum, cheerleaders); cheer++) {

      // Which team is cheering more?
      int next_state = 0;
      if (cheer > spoilify_cheers[time]) 
        next_state = max(state, 0) + 1;
      else if (cheer < spoilify_cheers[time])
        next_state = min(state, 0) - 1;

      score next = solve(time - 1, cheer_sum - cheer, next_state % 5);
      
      // Will a team score next minute?
      if (next_state == 5)
        next.sportify++;
      else if (next_state == -5)
        next.spoilify++;

      // Keep best available result.
      if (cheer == 0)
        now = next;
      else if (next > now)
        now = next;
    }
    return now;
  }
}

int main() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  
  // Read problem.
  cin >> cheerleaders >> cheer_length >> spy_reports;
  for (int i = 0; i < spy_reports; i++) {
    int from, to;
    cin >> from >> to;

    for (int j = from; j < to; j++)
      spoilify_cheers[MATCH_LENGTH-j]++;
  }
  
  // Solve.
  score result = solve(MATCH_LENGTH, cheerleaders*cheer_length, 0);
  
  // Print solution.
  cout << result.sportify << ' ' << result.spoilify << endl;
  
  return 0;
}
