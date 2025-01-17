#include <memory>
#include "graph.h"
#include <algorithm>
#include <iostream>


void *APPROX_VC_2(void *g_input)
{
    Graph_struct g_raph = *(const Graph_struct *)g_input;
    vector_vertices &cover = * new vector_vertices();

    while (g_raph.edge_no > 0) {
        unsigned vert1_p = 0, vert2_p;
        {
            size_t mvar;
            mvar = rand() % (g_raph.edge_no * 2);
            while (g_raph.adjacency_l[vert1_p].size() <= mvar) {
                mvar -= g_raph.adjacency_l[vert1_p].size();
                ++vert1_p;
            }
            vert2_p = g_raph.adjacency_l[vert1_p].front();
        }
        cover.push_back(vert1_p);
        cover.push_back(vert2_p);
        g_raph.clear(vert1_p );
        g_raph.clear(vert2_p );

    }
    std::sort(cover.begin(), cover.end(), std::less<int>());
    return &cover;
}

//
// Created by Jannat Sidhu on 2019-11-22.
//

