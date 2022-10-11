#include "mgraph.hpp"

#include <deque>
#include <iostream>
#include <queue>
#include <sstream>
using std::cout, std::endl;

using std::deque, std::priority_queue;

Target::Target(int to, int weight) : to(to), weight(weight) {}

From::From(int from, int weight) : from(from), weight(weight) {}

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

void mGraph::bfs(function<bool(const int current, const unordered_map<int, From>& visited)> fn,
                 bool only_not_visited /*= true*/) {
  // int - first -> current vertex index, int - second -> from vertex index
  unordered_map<int, From> visited({{root_, From(-1)}});

  // in pair: int - first -> current vertex index, int - second -> from vertex index
  struct Edge_ {
    int current;
    int from;
  };

  deque<Edge_> queue;

  // find all vertex which there is connection from root to them
  // for each iterator check if the key in iterator is valid
  for (auto it = map_of_pathes_.find(root_); it != map_of_pathes_.end() && (*it).first == root_;
       ++it) {
    queue.push_back(Edge_{.current = (*it).second.to, .from = (*it).first});
  }

  while (!queue.empty()) {
    Edge_& current = queue.front();
    queue.pop_front();

    // call fn if flag not set and break on return callback
    if (!only_not_visited && fn(current.current, visited)) {
      break;
    }

    // not add to queue if is visited
    if (visited.find(current.current) != visited.end()) {
      continue;
    }

    visited.insert({current.current, From(current.from)});

    for (auto it = map_of_pathes_.find(current.current);
         it != map_of_pathes_.end() && (*it).first == current.current; ++it) {
      // if candidate `(*it).second.to` now not equal to current from
      //  in other words if it is not graph <=> graph cycle
      if ((*it).second.to != current.from) {
        queue.push_back({(*it).second.to, current.current});
      }
    }

    // call fn if flag set and break on return callback
    if (only_not_visited && fn(current.current, visited)) {
      break;
    }
  }
}

void mGraph::dijkstra(function<bool(const int current, const unordered_map<int, From>& visited)> fn,
                      bool only_after_all_visited /*= false*/) {
  // int - first -> current vertex index, int - second -> from vertex index
  unordered_map<int, From> visited({{root_, From(-1, 0)}});

  // in pair: int - first -> current vertex index, int - second -> from vertex index
  struct Edge_ {
    int current;
    int from;
    int weight_to_current;
  };
  class Compare {
   public:
    bool operator()(Edge_& a, Edge_& b) { return a.weight_to_current > b.weight_to_current; };
  };

  priority_queue<Edge_, std::vector<Edge_>, Compare> queue;

  // find all vertex which there is connection from root to them
  // for each iterator check if the key in iterator is valid
  for (auto it = map_of_pathes_.find(root_); it != map_of_pathes_.end() && (*it).first == root_;
       ++it) {
    queue.push(Edge_{
        .current = (*it).second.to, .from = (*it).first, .weight_to_current = (*it).second.weight});
  }

  while (!queue.empty()) {
    Edge_ current = queue.top();
    queue.pop();

    // check queue if is visited and weight
    auto it = visited.find(current.current);
    if (it != visited.end()) {
      // if weight lesser update and continue
      if(it->second.weight > current.weight_to_current){
        it->second.from = current.from;
        it->second.weight = current.weight_to_current;
      } 
        continue;
    }else{
      visited.insert({current.current, From(current.from, current.weight_to_current)});

    }


    for (auto it = map_of_pathes_.find(current.current);
         it != map_of_pathes_.end() && (*it).first == current.current; ++it) {
      // if candidate `(*it).second.to` now not equal to current from
      //  in other words if it is not graph <=> graph cycle
      if ((*it).second.to != current.from) {
        queue.push({(*it).second.to, current.current, current.weight_to_current + it->second.weight});
      }
    }

    // call fn if flag set and break on return callback
    if (!only_after_all_visited && fn(current.current, visited)) {
      break;
    }
  }

  if(only_after_all_visited){
    fn(-1, visited);
  }
}

bool mGraph::present_cycle() {
  bool cycled = false;

  // closure with cycled variable
  auto func = [&cycled](int now, const unordered_map<int, From>& visited) {
    // for debug

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

void mGraph::set_root(const int a){
  root_set_ = true;
  root_ = a;
}