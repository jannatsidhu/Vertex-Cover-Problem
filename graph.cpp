#include "graph.h"

void Graph_struct::init(unsigned no_vertices){
    adjacency_l.clear();
    edge_no = 0;
    adjacency_l.resize(no_vertices, {});
}

void Graph_struct::add(Edge_struct edg) {
    auto &lis1 = adjacency_l[edg.v1];
    auto &lis2 = adjacency_l[edg.v2];
    lis1.push_back(edg.v2);
    lis2.push_back(edg.v1);
    edge_no ++;
}
