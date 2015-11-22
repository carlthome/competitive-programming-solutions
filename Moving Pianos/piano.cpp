#include <iostream>
#include <vector>
#define MAX_TESTS 100
#define MAX_PIANOS 1000
#define MAX_TUNERS 2000
#define MAX_DAYS 100
#define FINE 1
#define WEEKEND_WORK 0
#define SERIOUS_TROUBLE -1

using namespace std;

//template<typename T> using matrix = vector<vector<T>>;

typedef vector<vector<int>> matrix;

inline bool is_workday(int day) {
  return (day % 7) < 5;
}

inline bool is_weekend(int day) {
  return !is_workday(day);
}

int move_pianos(matrix move_orders, int piano_tuners) {

  // Tuners work in pairs!
  int tuner_pairs = piano_tuners/2; 
  
  // Calculate how many pianos are left to move each day.
  for (int i = 0; i < MAX_DAYS; i++) {
    int sum = move_orders[i][i];
    for (int j = i-1; j >= 0; j--) {
      sum += move_orders[j][i];
      move_orders[j][i] = sum;
    }
  }
  
  
  // Calculate constraints.
  int constraints[MAX_DAYS][MAX_DAYS] = {{0}};
  for (int i = 0; i < MAX_DAYS; i++)
    constraints[i][i] = move_orders[i][i];
  for (int i = 1; i < MAX_DAYS; i++)
    for (int j = 0; j < MAX_DAYS-i; j++)
      constraints[j][j+i] = constraints[j][j+i-1] + move_orders[j][j+i];

  // Validate constraints. Make sure enough workforce is available.
  int result;
  bool weekend = false;
  for (int end = 0; end < MAX_DAYS; end++) {
    int work_days = 0;

    for (int begin = end; begin >= 0; begin--) {
      if (is_workday(begin))
        work_days++;

      if (tuner_pairs * work_days < constraints[begin][end]) {
        weekend = true;

        if (tuner_pairs * (end-begin+1) < constraints[begin][end])
          return SERIOUS_TROUBLE;
      }
    }
  }
  return (weekend) ? WEEKEND_WORK : FINE;
}

int main() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  
  int tests;
  cin >> tests;
  for (int test = 0; test < tests; test++) {
  
    // Read problem.
    int m, p;
    cin >> m >> p;

    matrix move_orders(MAX_DAYS, vector<int> (MAX_DAYS, 0));
    for (int j = 0; j < m; j++) {
      int b, e;
      cin >> b >> e;
      move_orders[b-1][e-1]++;
    }

    // Solve.
    int result = move_pianos(move_orders, p);

    // Print solution.
    print_solution:
    switch (result) {
      case(FINE):
        cout << "fine" << endl;
        break;
      case(WEEKEND_WORK):
        cout << "weekend work" << endl;
        break;
      case(SERIOUS_TROUBLE):
        cout << "serious trouble" << endl;
        break;
    }
  }

  return 0;
}
