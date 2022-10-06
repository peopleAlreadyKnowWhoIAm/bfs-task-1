#include "mgraph.hpp"

#include <deque>
#include <iostream>
#include <sstream>
using std::cout, std::endl;

using std::deque;

mGraph::Target::Target(int to, int weight) : to(to), weight(weight) {}

mGraph::mGraph() {}

mGraph::mGraph(vector<Edge>& edges) {
  for (auto&& i : edges) {
    insert(i);
  }
}

void mGraph::insert(Edge edge) {
  // save root to navigate from
  if (!root_set_) {
    root_ = edge.from;
    root_set_ = true;
  }

  this->map_of_pathes_.insert({edge.from, Target(edge.to, edge.weight)});

  // save reverse path if it unordered
  if (edge.unordered) {
    this->map_of_pathes_.insert({edge.to, Target(edge.from, edge.weight)});
  }
}

void mGraph::bfs(
    function<bool(const int from, const int current, const unordered_map<int, int>& visited)> fn,
    bool only_not_visited /*= true*/) {
  // int - first -> current vertex index, int - second -> from vertex index
  unordered_map<int, int> visited({{root_, -1}});

  // in pair: int - first -> current vertex index, int - second -> from vertex index
  deque<pair<int, int>> queue;

  // find all vertex which there is connection from root to them
  // for each iterator check if the key in iterator is valid
  for (auto it = map_of_pathes_.find(root_); it != map_of_pathes_.end() && (*it).first == root_;
       ++it) {
    queue.push_back({(*it).second.to, (*it).first});
  }

  while (!queue.empty()) {
    pair<int, int>& current = queue.front();
    queue.pop_front();

    // call fn if flag not set and break on return callback
    if (!only_not_visited && fn(current.second, current.first, visited)) {
      break;
    }

    // not add to queue if is visited
    if (visited.find(current.first) != visited.end()) {
      continue;
    }

    visited.insert({current.first, current.second});

    for (auto it = map_of_pathes_.find(current.first);
         it != map_of_pathes_.end() && (*it).first == current.first; ++it) {
      // if candidate `(*it).second.to` now not equal to current from
      //  in other words if it is not graph <=> graph cycle
      if ((*it).second.to != current.second) {
        queue.push_back({(*it).second.to, current.first});
      }
    }

    // call fn if flag set and break on return callback
    if (only_not_visited && fn(current.second, current.first, visited)) {
      break;
    }
  }
}

bool mGraph::present_cycle() {
  bool cycled = false;

  // closure with cycled variable
  auto func = [&cycled](int from, int now, const unordered_map<int, int>& visited) {
    // for debug
    cout << "From: " << from << ", now: " << now << endl;

    if (visited.find(now) != visited.end()) {
      cycled = true;
      return true;
    }
    return false;
  };

  // must flag be down because index need to be checked before filtered whether visited
  bfs(func, false);
  return cycled;
}

string mGraph::to_string() const {
  std::stringstream buf;
  for (auto&& i : map_of_pathes_) {
    buf << i.first << "->" << i.second.to << std::endl;
  }
  return buf.str();
}