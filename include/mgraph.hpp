#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::vector, std::string, std::unordered_multimap, std::unordered_map, std::pair,
    std::function;

/**
 * @brief Help structure to insert graphs
 * 
 */
struct Edge {
  int from = -1;
  int to = -1;
  int weight = 0;
  bool unordered = true;
};

/// @brief My implementation of graph
class mGraph {
  struct Target {
    Target(int to, int weight = 0);
    int to;
    int weight = 0;
  };

  int root_;

  bool root_set_ = false;
  unordered_multimap<int, Target> map_of_pathes_;

 public:
  mGraph();
  mGraph(vector<Edge>& list_of_edges);

  /**
   * @brief Insert edge into
   * 
   * @param edge to insert. Also add all unique vertex
   */
  void insert(Edge edge);

  /**
   * @brief Broad First Search. Never go graph <=> graph cycle
   * 
   * @param fn function callback
   * fn @param from vertex index
   * fn @param current vertex index
   * fn @param visited map<visited index, from vertex>
   * @param only_not_visited flag when call `fn`. If set call after skipping visited,
   *                         else before(could be used for search cycles)
   */
  void bfs(
      function<bool(const int from, const int current, const unordered_map<int, int>& visited)> fn,
      bool only_not_visited = true);

  /**
   * @brief Check whether is cycles which include more than 2 nodes
   * 
   * @return true if present
   * @return false if absent
   */
  bool present_cycle();

  /**
   * @brief Convert graph into text with adjecent list
   * 
   * @return string of adjecent list
   */
  string to_string() const;
};