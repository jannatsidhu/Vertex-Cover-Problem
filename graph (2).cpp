#include "graph.h"
#include "iostream"

void graph::clear_g(){
    for (auto &m:adjacenymatrix)
        for(auto &n : m)
            n=INDEF; // we set the distance between all vertices in the 2D vector to be very very high
    path.clear();
}

void graph::initialise_g(unsigned int num_of_vertices)
{
    num_v = num_of_vertices;
    adjacenymatrix.clear(); // we clear both vectors whenever a new V command is called
    path.clear();
    adjacenymatrix.resize(num_v); //resize the vector with new length i.e. V
    for (auto &m:adjacenymatrix)
    {                                       // to resize the vector corresponding to each m in vertices leng vector
        m.resize(num_v, INDEF); // we set the distance between all vertices in the 2D vector to be very very high
    }
}

void graph::addEdge(unsigned int vertex_1, unsigned int vertex_2)
{
    if (vertex_1 >= adjacenymatrix.size() || vertex_2 >= adjacenymatrix[0].size()) {
        throw "There exists a vertex that is not in the specified range! ";
    }
        // else  if (vertex_1 == vertex_2) {
        //     throw "There exists a vertex that has an edge to itself: NOT ALLOWED! ";
        // }
    else
    {
        adjacenymatrix[vertex_1][vertex_2] = 1; // we initialise the edge values to be 1 both from v1 to v2 and v2 to v1
        adjacenymatrix[vertex_2][vertex_1] = 1;
    }
}


void graph::shortest_path(unsigned int src_vertex, unsigned int dest_vertex) {
    if (src_vertex == dest_vertex)
    {
        std::cout<<src_vertex<<"-"<<dest_vertex;
    }
    else
    {
        if (src_vertex >= num_v || dest_vertex >= num_v)
        {
            throw "Cannot find shortest path for vertices that are not in the specified range! ";
        }

        unsigned int visited[num_v]; //visited array for vertices that are visited
        unsigned int distance[num_v]; // distance array contains distance of a vertex from source vertex: we keep adding vertice distances here
        unsigned int updated_distance;
        path.clear(); // ensure that path vector is empty

        for (unsigned int i = 0; i < num_v; i++)
        {
            visited[i] = 0; // setting visited 0 for all vertices when starting the comparision
            distance[i] = adjacenymatrix[src_vertex][i]; // setting the distance of i from source vertex if there is a direct edge
        }

        visited[src_vertex] = 1;  // by BFS algo, set src vertex to be visited i.e. 1 to start
        distance[src_vertex] = 0; // and dist of src vertex from itself is 0

        for (unsigned int i = 1; i < num_v; i++)
        {

            unsigned int minimum_distance = INDEF; // set minimum distance to be very large, if there will be a shorter path, then we'll replace indef with that
            unsigned int k = 0;
            for (unsigned int any_vert_i = 0; any_vert_i < num_v; any_vert_i++)
            {
                if (visited[any_vert_i] == 0 && distance[any_vert_i] < minimum_distance)  // if a vert is not visited and its distance from src is less then infinite then replace the min dist with this distance
                {
                    minimum_distance = distance[any_vert_i];
                    k = any_vert_i;
                    //std::cout<<" k = "<<k; std::cout<<" md = "<<minimum_distance;
                }
            }

            visited[k] = 1; // mark this vertex as visited now
            //  now we see neighbours of k

            for (unsigned int j = 0; j < num_v; j++)
            {
                updated_distance = (adjacenymatrix[k][j] == INDEF ? INDEF : (minimum_distance + adjacenymatrix[k][j])); // if there is no edge form k to v then indef, else we set the new dist to be dist of k from src + dist of j from k
                if (visited[j] == 0 && (updated_distance < distance[j])) //remove already visited vertices and check if a shorter distance exists
                {
                    distance[j] = updated_distance;  // new distance j contains dist of k from src + dist of k from its neighbour
                    //std::cout<<" j = "<<j; std::cout << "new dist= " << updated_distance;

                }
            }
        }

        if (distance[dest_vertex] == INDEF)  // if dist of destination is still infinite, means it is not connected to src by any path
        {
            throw "There exists no path between the source and destination vertex! ";
        }

        // Adding the shortest path vertices into path vector and forming a path
        unsigned int vertex = dest_vertex;

        while (distance[vertex] > 0)
        {
            path.push_back(vertex);  // adding our shortest path to vector
            for (size_t any_v_i = 0; any_v_i < num_v; ++any_v_i)
            {
                if (adjacenymatrix[vertex][any_v_i] < INDEF && distance[any_v_i] + adjacenymatrix[vertex][any_v_i] == distance[vertex])  // there exists an edge and it is the edge of closest neighbour i.e shortest path
                {
                    // dist of any vert i from src + edge between considered_vertex and i = dist of considered_vertex from src // this should be equal for smallest path! although any 1st vert to satisfy this will be considered
                    vertex = any_v_i;
                    break;
                }
            }
        }
        path.push_back(vertex);

        //PRINTING using rbegin rend functions of vector
        for (auto iterator = path.rbegin(); iterator != path.rend(); iterator++)
        {
            std::cout << *iterator;
            if (iterator != path.rend() - 1)
                std::cout << "-";
            else
                std::cout << "\n";
        }
    }
}

