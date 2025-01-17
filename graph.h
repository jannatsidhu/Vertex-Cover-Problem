#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <list>
#include <vector>


struct Edge_struct{
    unsigned v1,v2;
};

typedef std::list<unsigned > list_vertices;
typedef std::vector<unsigned> vector_vertices;
typedef std::vector<list_vertices> adjacency_list;

struct Graph_struct{
    std::size_t edge_no;
    adjacency_list adjacency_l;

    void init(unsigned no_vertices);
    void add(Edge_struct edg);
    void clear(unsigned v);
};

#endif
