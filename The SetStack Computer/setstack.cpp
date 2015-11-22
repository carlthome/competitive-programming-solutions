#include<iostream>
#include<string>
#include<stack>
#include<set>
#include<map>

using namespace std;

typedef struct set_stack {
  stack<set<long>> sets;
  map<set<long>, long> ids;
  long id;

  set_stack() : id(0) {};

  long PUSH() {
    set<long> s;
    sets.push(s);

    return sets.top().size();
  }

  long DUP() {
    sets.push(sets.top());

    return sets.top().size();
  }

  long UNION() {
    set<long> s1 = sets.top();
    sets.pop();
    set<long> s2 = sets.top();
    sets.pop();

    for (auto i : s1)
      s2.insert(i);
    sets.push(s2);

    return sets.top().size();
  }

  long INTERSECT() {
    set<long> s1 = sets.top();
    sets.pop();
    set<long> s2 = sets.top();
    sets.pop();

    set<long> s3;
    for (auto i : s1)
      if(s2.find(i) != s2.end())
        s3.insert(i);
    sets.push(s3);

    return sets.top().size();
  }

  long ADD() {
    set<long> s1 = sets.top();
    sets.pop();
    set<long> s2 = sets.top();
    sets.pop();

    if(s1.empty())
      s2.insert(0);
    else {
      if (ids.find(s1) == ids.end())
        ids[s1] = ++id;
      s2.insert(ids[s1]);
    }
    sets.push(s2);

    return sets.top().size();
  }
} set_stack;

int main() {
  long T, N;
  string command;

  cin >> T;
  while (T--) {
    set_stack s;
    cin >> N;
    while (N--) {
      cin >> command;
      if (command == "PUSH")
        cout << s.PUSH() << endl;
      else if (command == "DUP")
        cout << s.DUP() << endl;
      else if (command == "UNION")
        cout << s.UNION() << endl;
      else if (command == "INTERSECT")
        cout << s.INTERSECT() << endl;
      else if (command == "ADD")
        cout << s.ADD() << endl;
    }
    cout << "***" << endl;
  }

  return 0;
}