#include <algorithm>
#include <iostream>
#include <memory>
#include "graph.h"
#include "minisat/core/Solver.h"


void *APPROX_VC_3(void *igraph)
{
    const Graph_struct &graph_input = *(const Graph_struct *)igraph;
    vector_vertices &cvar = *new vector_vertices();


    unsigned int k = 0;
    bool res;
    unsigned int lw = 0;
    unsigned int adl_size = graph_input.adjacency_l.size();
    k= (adl_size + lw) / 2;

    while (lw <= adl_size)
    {

        std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
        std::vector<std::vector<Minisat::Lit>> xij_matrix(graph_input.adjacency_l.size());
        for (unsigned int i = 0; i < graph_input.adjacency_l.size(); i++)
            for (unsigned int j = 0; j < k; j++) {
                Minisat::Lit l = Minisat::mkLit(solver->newVar());
                xij_matrix[i].push_back(l);
            }
        // first condition: At least one vertex is the ith vertex in the vertex cover
        for (unsigned int i = 0; i < k; i++) {
            Minisat::vec<Minisat::Lit> new_lit;
            for (unsigned int j = 0; j < graph_input.adjacency_l.size(); j++) {
                new_lit.push(xij_matrix[j][i]);
            }
            solver->addClause(new_lit);
        }

        // second condition: No one vertex can appear twice in a vertex cover
        for (unsigned int m = 0; m < graph_input.adjacency_l.size(); m++)
            for (unsigned int p = 0; p < k; p++)
                for (unsigned int q = p + 1; q < k; q++) {
                    solver->addClause(~xij_matrix[m][p], ~xij_matrix[m][q]);
                }
        //third condition: No more than one vertex appears in the mth position of the vertex cover.
        for (unsigned int m = 0; m < k; m++)
            for (unsigned int p = 0; p < graph_input.adjacency_l.size(); p++)
                for (unsigned int q = p + 1; q < graph_input.adjacency_l.size(); q++) {
                    solver->addClause(~xij_matrix[p][m], ~xij_matrix[q][m]);
                }


        //forth condition: Every edge is incident to at least one vertex in the vertex cover.
        for(unsigned vert1 = 0 ; vert1 < graph_input.adjacency_l.size(); ++vert1) {
            for (auto vert2 : graph_input.adjacency_l[vert1]) {
                if(vert2 < vert1) continue;
                Minisat::vec<Minisat::Lit> e_lit;
                for (unsigned int it = 0; it < k; it++) {
                    e_lit.push(xij_matrix[vert1][it]);
                    e_lit.push(xij_matrix[vert2][it]);
                }

                solver->addClause(e_lit);
            }
        }
        res = solver->solve();
        if (res )
        {
            cvar.clear();
            for (unsigned int i = 0; i < graph_input.adjacency_l.size(); i++)
                for ( unsigned int j =0; j < k; j++)
                    if (Minisat::toInt(solver->modelValue(xij_matrix[i][j])) == 0)
                    {
                        cvar.push_back(i);
                    }

            adl_size = k - 1;
        }
        else {
            solver.reset(new Minisat::Solver());
            lw = k + 1;
        }
        k = (adl_size + lw) / 2;
    }
    std::sort(cvar.begin(), cvar.end(), std::less<int>());

    return &cvar;


}

//
// Created by Jannat Sidhu on 2019-11-22.
//

