#include "mgraph.hpp"

#include <sstream>

mGraph::Target::Target(int to, int weight)
:to(to), weight(weight){}

mGraph::mGraph() {}

mGraph::mGraph(vector<Edge>& edges) {
    root_set_ = true;
    root_ = edges[0].from;
    for (auto&& i : edges) {
        this->map_of_pathes_.insert({ i.from , Target(i.to, i.weight)});
        if (i.unordered) {
            this->map_of_pathes_.insert({ i.to , Target(i.from, i.weight)});
        }
    }

}

void mGraph::insert(Edge& edge) {
    if(!root_set_){
        root_ = edge.from;
    }

    this->map_of_pathes_.insert({ edge.from , Target(edge.to, edge.weight)});
    if (edge.unordered) {
        this->map_of_pathes_.insert({ edge.to , Target(edge.from, edge.weight)});
    }
} 

void mGraph::bfs() {

}

bool mGraph::present_cycle() const{
    return false;
}

string mGraph::to_string() const {
    std::stringstream buf;
    for (auto &&i : map_of_pathes_)
    {
     buf<<i.first<<"->"<<i.second.to<<std::endl;   
    }
    return buf.str();
}