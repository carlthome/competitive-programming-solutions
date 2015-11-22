#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

struct point { int x, y; };
typedef vector<point> polygon;

point operator - (point p, point q) { return {p.x-q.x, p.y-q.y}; }
int operator * (point p, point q) { return p.x*q.x + p.y*q.y; }
int operator ^ (point p, point q) { return p.x*q.y - p.y*q.x; }
double abs(point p) { return sqrt(p*p); };

double distance(point p, point q1, point q2) {
  double d;
  if ((p-q1)*(q2-q1) < 0) d = abs(p-q1);
  else if ((p-q2)*(q1-q2) < 0) d = abs(p-q2);
  else d = abs((p-q1)^(q2-q1)) / abs(q2-q1);
  return d / 2;
}

int main() {
  int tc, n;
  cin>>tc;
  while (tc--) {
    cin >> n;
    polygon p1 (n);
    for (int i = 0; i < n; ++i) cin >> p1[i].x, cin >> p1[i].y;

    cin >> n;
    polygon p2 (n);
    for (int i = 0; i < n; ++i) cin >> p2[i].x, cin >> p2[i].y;

    double max = 1000;
    for (int i = 0; i < p1.size(); ++i)
      for (int j = 0; j < p2.size(); ++j) {
        max = min(max, distance(p1[i], p2[j], p2[(j+1) % p2.size()]));
        max = min(max, distance(p2[j], p1[i], p1[(i+1) % p1.size()]));
      }
    cout << setprecision(8) << max << endl;
  }

  return 0;
}
