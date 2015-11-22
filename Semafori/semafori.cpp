#include <iostream>
#include <vector>
using namespace std;

int main() {	
  ios::sync_with_stdio(false);
  cin.tie(NULL);
 
  int time = 0;
  int distance = 0;
  int N, L;
  cin >> N >> L;
  
  for (int i = 0; i < N; ++i) {
    int D, R, G;
    cin >> D >> R >> G;
    //cerr << D << ' ' << R << ' ' << G << ' ' << endl;
    time += D-distance;
    distance = D;
    const auto n = time % (R+G);
    //cerr << "Time: " << time << ", Distance: " << distance << ", n: " << n << endl;
    if (n < R) 
      time += R-n;
  }
  
  time += L - distance;
  
  cout << time;
  
  return 0;
}