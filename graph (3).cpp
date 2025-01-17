#include "graph.h"
#include <algorithm>

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

void Graph_struct::clear(unsigned vert){
    if(vert >= adjacency_l.size()) return;
    for(auto u : adjacency_l[vert]){
        auto &lis2 = adjacency_l[u];
        auto it = std::find(lis2.begin(), lis2.end(), vert);
        if(it != lis2.end()){
            lis2.erase(it);
            --edge_no;
        }
    }
    adjacency_l[vert].clear();
}



//
// Created by Jannat Sidhu on 2019-11-22.
//

