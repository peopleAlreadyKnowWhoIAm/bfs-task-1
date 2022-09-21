#pragma once

#include <vector>
#include <string>
#include <unordered_map>

using std::vector, std::string, std::unordered_multimap;

struct Edge {
    int from;
    int to;
    int weight = 0;
    bool unordered = true;
};




/// @brief My implementation of graph. Uses only edges.
class mGraph {
    struct Target{
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

    void insert(Edge&);

    void bfs();

    bool present_cycle() const;

    string to_string() const;
};