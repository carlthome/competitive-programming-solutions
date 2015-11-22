// Author: Carl Thomé

#ifndef INTERVAL_COVER_H
#define INTERVAL_COVER_H
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>

// An interval is a range between [min..max].
typedef struct interval {
  size_t id;
  double min, max;
  interval(double _min, double _max, size_t _id) : min(_min), max(_max), id(_id) {}
} interval;

// Try to cover the goal interal with intervals in the domain. 
// Returns the id:s of the least intervals required to cover the goal.
std::vector<int> cover(interval goal, std::vector<interval> domain) {
  using namespace std;

  vector<int> intervals;
  
  // Sort intervals by lower bound.
  sort(
    domain.begin(), 
    domain.end(),
    [] (const interval & a, const interval & b) -> bool { return a.min < b.min;}
  );
  
  // Go through the domain and select intervals to cover the goal interval.
  double lower_bound = goal.min;
  double upper_bound = goal.max;
  for (int i = 0; i < domain.size(); i++) {

    // Greedily find the longest acceptable interval.
    double floor = -DBL_MAX;
    bool floor_moved = false;
    for (int j = i; j < domain.size(); j++) {      
      if (domain[j].min > lower_bound)
        break;
      if (domain[j].max > floor) {
        floor = domain[j].max;
        floor_moved = true;
        i = j;
      }
    }

    // If the floor couldn't be raised, abort.
    if (!floor_moved)
      break;

    // Store interval and update range to cover.
    if (floor >= lower_bound) {

      // Raise the floor and remember which interval enabled this.
      lower_bound = floor;
      intervals.push_back(domain[i].id);
      
      // Covered? Otherwise keep at it!
      if (lower_bound >= upper_bound)
        return intervals;
    }
  }

  // The goal interval could not be covered. Assume this by default.
  return {};
}

#endif /* INTERVAL_COVER_H */
