#include <vector>
using namespace std;

class graph {
#define INDEF   (~(0x1<<31))
private:
    unsigned int num_v;
    vector<vector<unsigned int>> adjacenymatrix; // to store edges between vertices, we take this vector matrix
    vector<unsigned> path; // to store the vertices that make the shortest path

public:
    void clear_g();
    void initialise_g(unsigned int num_of_vertices);
    void addEdge(unsigned int vertex_1, unsigned int vertex_2);
    void shortest_path(unsigned int src_vertex, unsigned int dest_vertex);
};
