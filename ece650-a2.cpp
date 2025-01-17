#include <iostream>
#include <sstream>
#include "graph.h"

int main(int argc, char **argv) {

    char user_input;
    int num_of_vertices,src_vertex,dest_vertex, order_flag_v = 0, order_flag_e = 0;
    string all_edges_in_curly_braces, line;
    graph g; // instance of graph class

    // read from stdin until EOF
    while (getline(cin, line))
    {
        istringstream input(line);
        while (input >> user_input)
        {  // extracting values from input stream

            try
            {
                switch (user_input)
                {
                    case 'V' :
                    {
                        if (order_flag_v == 1)
                        {
                            order_flag_v = 0;
                            throw "Cannot specify vertices twice! Start Again! ";
                        }
                        else
                        {
                            input >> num_of_vertices; //extracting number of vertices from input stream
                            if(num_of_vertices < 0)
                            {
                                throw "Invalid Input ";
                            }
                            std::cout<<"V "<<num_of_vertices<<std::endl;
                            g.initialise_g(num_of_vertices);
                            order_flag_v = 1;
                            order_flag_e = 0;
                            break;
                        }
                    }

                    case 'E' :
                    {
                        if ( order_flag_e == 1 )
                        {
                            if (order_flag_v == 1)
                                order_flag_e = 0;
                            throw "Cannot specify edges twice! Start Again! ";
                        }

                        else
                        {
                            order_flag_e = 1;
                            order_flag_v = 0;
                            g.clear_g();
                            input >> all_edges_in_curly_braces; //here we extract the string after E
                            std::cout <<"E "<< all_edges_in_curly_braces<<std::endl;
                            istringstream all_edges(all_edges_in_curly_braces);
                            char separtator;
                            unsigned int vertex_1, vertex_2;
                            all_edges >> separtator; // extract the {
                            while (separtator != '}')  // till we reach end of this string }
                            {
                                all_edges >> separtator; // extract the < bracket
                                if (separtator == '}') break;
                                all_edges >> vertex_1;
                                all_edges >> separtator; // extract the , comma
                                all_edges >> vertex_2;
                                g.addEdge(vertex_1, vertex_2);
                                all_edges >> separtator; // extract > bracket after each edge
                                all_edges >> separtator; // extract , comma separating the edges
                            }
                        }
                        break;
                    }

                    case 's':
                    {
                        input >> src_vertex;
                        input >> dest_vertex;
                        g.shortest_path(src_vertex, dest_vertex);
                        break;
                    }

                    default:
                    {
                        std::cerr << "Error: Incorrect Input Format!"<< endl;
                        break;
                        break;
                    }
                }
            }
            catch (const char* error)
            {
                std::cerr << "Error: " << error << endl;
            }
        }
    }
    return 0;
}




