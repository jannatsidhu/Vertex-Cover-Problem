#include <memory>
#include "graph.h"
#include <algorithm>
#include <iostream>


void *APPROX_VC_1(void *g1_input)
{
    Graph_struct g_raph1 = *(const Graph_struct *)g1_input;
    vector_vertices &cover1 = *new vector_vertices();

    while(g_raph1.edge_no > 0){
        auto v = std::max_element(
                g_raph1.adjacency_l.begin(), g_raph1.adjacency_l.end(),
                [](list_vertices &l1, list_vertices &l2)->bool{ return l1.size() < l2.size(); }
        );
        unsigned i = (unsigned)(v - g_raph1.adjacency_l.begin());
        cover1.push_back(i);
        g_raph1.clear(i);
    }
    std::sort(cover1.begin(), cover1.end(), std::less<int>());
    return &cover1;

}

//
// Created by Jannat Sidhu on 2019-11-22.
//

