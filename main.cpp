#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "mgraph.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  mGraph m;
  string buf;

  // Data load section
  getline(cin, buf);  // Data of num of vertexes and edges - ignore
  getline(cin, buf);  // Users

  istringstream iss_user_buf(buf);

  unordered_set<int> users;

  unordered_set<int> routers;

  while (!iss_user_buf.eof()) {
    int buf;
    iss_user_buf >> buf;
    users.insert(buf);
  }

  do {
    getline(cin, buf);
    if (buf.empty()) {
      break;
    }
    istringstream iss_buf(buf);
    int from, to, weight;
    iss_buf >> from;
    iss_buf >> to;
    iss_buf >> weight;
    m.insert(Edge{.from = from, .to = to, .weight = weight});

    if (users.find(from) == users.cend()) {
      routers.insert(from);
    }

    if (users.find(to) == users.cend()) {
      routers.insert(to);
    }
  } while (true);
  // Data load section

  vector<int> max_ping_for_each;
  max_ping_for_each.reserve(routers.size());

  for (auto &&router : routers) {
    int max_ping_buf = -1;
    auto fun = [&max_ping_buf, &users](const int current, const unordered_map<int, From> &visited) {
      for (auto &&pair : visited) {
        if (pair.second.from != -1 && users.find(pair.first) != users.cend() &&
            max_ping_buf < pair.second.weight) {
          max_ping_buf = pair.second.weight;
        }
      }
      return false;
    };

    m.set_root(router);
    m.dijkstra(fun, true);

    max_ping_for_each.push_back(max_ping_buf);
  }

  int min_ping_for_server = *min_element(max_ping_for_each.cbegin(), max_ping_for_each.cend());

  cout << min_ping_for_server << endl;

  return 0;
}
