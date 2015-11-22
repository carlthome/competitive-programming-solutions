#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <map>
#include <set>
#include <queue>
using namespace std;

typedef pair<int,int> vertex;
typedef map<vertex, set<vertex>> graph;

int main()
{
  // Read input as strings.
  vector<string> b;
  for (string l; getline(cin, l);) b.push_back(l);

  // Translate Sokoban to graph problem.
  graph g;
  vertex start;
  set<vertex> goals;
  for (int i = 0; i < b.size(); ++i) for (int j = 0; j < b[i].size(); ++j) {
    const auto& c = b[i][j];

    auto add_vertex = [&]() {
      g[{i-1,j}].insert({i,j}); // Up
      g[{i+1,j}].insert({i,j}); // Down
      g[{i,j-1}].insert({i,j}); // Left
      g[{i,j+1}].insert({i,j}); // Right
    };
    auto add_goal = [&]() {
      goals.insert({i,j});
    };
    auto add_start = [&]() {
      start = {i,j};
    };

    switch (c) {
      case '#': /* Wall */ continue;
      case '$': /* Box */ continue;
      case '*': /* Box on goal */ continue;
      case ' ': /* Free space */ add_vertex(); break;
      case '.': /* Goal */ add_goal(); add_vertex(); break;
      case '@': /* Sokoban player */ add_start(); add_vertex(); break;
      case '+': /* Sokoban player on goal */ add_start(); add_vertex(); add_goal(); break;
    }
  }
  
  // Solve graph problem.
  auto found = false;
  queue<vertex> q;
  map<vertex, vertex> parents;
  map<vertex, bool> visited;
  vertex goal;
  q.push(start);
  const vertex end = {-1,-1};
  parents[start] = end;
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    if (goals.find(v) != goals.end()) { 
      goal = *goals.find(v);
      found = true; 
      break;
    }
    if (visited.find(v) == visited.end()) {
      visited[v] = true;
      for (vertex n : g[v]) {
        if (visited.find(n) != visited.end()) continue;
        q.push(n);
        parents[n] = v;
      }
    }
  }
  
  // Translate graph problem to Sokoban.
  string path = "";
  if (found) {
    vertex v = goal;
    while (parents[v] != end) {
      path += " ";
      auto dy = v.first - parents[v].first;
      auto dx = v.second - parents[v].second;
      if (dy == -1) path += "U";
      if (dy == 1) path += "D";
      if (dx == 1) path += "R";
      if (dx == -1) path += "L";
      v = parents[v];
    }
    path = string(path.rbegin(), path.rend());
  } else {
    path = "no path";
  }

  // Output path as string.
  cout << path << endl;
  cerr << endl;
  return 0;
}

