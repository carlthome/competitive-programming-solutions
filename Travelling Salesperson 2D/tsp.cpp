#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <limits>
#include <random>
#include <cmath>
#include <ctime>
#define CITIES 1000
#define TIME_LIMIT 1.8
#define NEIGHBORHOOD 25
using namespace std;
typedef vector<short> tour;
int ds[CITIES][CITIES];
int ns[CITIES][CITIES];

// Calculate tour length for the given tour.
inline unsigned long length(const tour& p) {
  auto l = 0;
  for (unsigned i = 1; i < p.size(); ++i) l += ds[p[i-1]][p[i]];
  l += ds[p[p.size()-1]][p[0]];
  return l;
}

// Find decent tour of size n with nearest neighbor.
inline tour nearest_neighbor(int n) {
  tour p (n);
  
  // Always start tour in city 0.
  p[0] = 0;
  
  // Enumerate cities.
  list<short> l;
  for (int i = 1; i < n; ++i) l.emplace_back(i % n);
  
  // Visit all remaining cities by nearest first.
  for (int i = 1; i < n; ++i) {
  
    auto min = l.begin();
    for (auto k = l.begin(); k != l.end(); ++k) {
      const auto d1 = ds[p[i-1]][*k], 
                 d2 = ds[p[i-1]][*min];
      if (d1 < d2) min = k;
    }
    
    p[i] = *min;
    l.erase(min);
  }
  
  return p;
}

inline void rev(tour& p, vector<int>& indices, int s, int e) {
  const int& n = p.size();
  
  int i = s - 1, j = e, diff = -1;
  if (i + 1 < j) diff = j - (i + 1);
  else diff = n - (i + 1) + j + 1;

  diff = (diff + 1) / 2;
  
  int start = i + 1, end = j;
  while (diff-- > 0) {
    start %= n;
    end = end == -1 ? n - 1 : end;
    swap(p[start++], p[end--]);
  }

  for (int i = 0; i < n; ++i) indices[p[i]] = i;
}

inline void optimize(tour& p, vector<int>& indices) {
  const auto& n = p.size();
  bool improved = true;
  while (improved) {
    improved = false;
    for (unsigned i = 0; i < n - 1; ++i) {     
      for (int k = 0; k < min((int)n, NEIGHBORHOOD); ++k) {
        const short& a = p[i],
                     b = p[i + 1],
                     c = ns[a][k],
                     d = p[(indices[ns[a][k]] + 1) % n];

        if (b == c or b == d) continue;

        if (ds[a][c] + ds[b][d] < ds[a][b] + ds[c][d]) {         
          improved = true;
          rev(p, indices, i + 1, indices[ns[a][k]]);
        }
      }
    }
  }
}

// Perturb a little.
inline void perturb(tour& p, vector<int>& indices) {
  const auto n = p.size();
  if (n < 8) return;
  
  static random_device rd;
  static uniform_int_distribution<int> d(2, n - 3);
  static auto r = bind(d, ref(rd));

  for (unsigned i = 0; i < n / 10; ++i) {
    auto pos = r();
    int i1 = pos - 1;
    int i2 = pos + 1;
    swap(p[i1], p[i2]);
    indices[p[i2]] = i2;
    indices[p[i1]] = i1;
  }
}

int main() {
  auto begin = clock();

  // Read graph and calculate distances. Note that the distance matrix is symmetrical.
  int n;
  cin >> n;
  vector<float> xs(n), ys(n);
  for (int i = 0; i < n; ++i) cin >> xs[i] >> ys[i];
  for (int i = 0; i < n; ++i)
    for (int j = i; j < n; ++j)
      ds[i][j] = ds[j][i] = round(sqrt(pow(xs[i]-xs[j], 2) + pow(ys[i]-ys[j], 2)));
      
  // Calculate nearest neighbors matrix. Note that the 0:th closest neighbor is the node itself.
  for (int i = 0; i < n; ++i) {
    for (long j = 0; j < n; ++j) ns[i][j] = j;
    sort(ns[i], ns[i] + n, [&i](const short& a, const short& b) -> bool { 
      return ds[i][a] < ds[i][b];
    });
  }

  // Construct decent tour with nearest neighbor.
  auto p = nearest_neighbor(n);
  
  // Store indices for constant lookup.
  vector<int> indices (n);
  for (int i = 0; i < n; ++i) indices[p[i]] = i;
  
  optimize(p, indices);

  int best = length(p);
  tour shortest = p;

  // Perturb and optimize for as long as possible.
  while (double(clock() - begin) / CLOCKS_PER_SEC < TIME_LIMIT) {
    perturb(p, indices);
    optimize(p, indices);
    int l = length(p);
    if (l < best) {
      shortest = p;
      best = l;
    }
  }

  for (const auto v : shortest) cout << v << endl;
}
