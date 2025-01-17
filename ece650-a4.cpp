#include <iostream>
#include <sstream>
#include "graph.h"
#include "minvc.h"
using std::toupper;

int main(int argc, char **argv)
{
    char u_input;
    string line;
    unsigned int no_v = 0;
    Graph_struct &graph_input = *new Graph_struct();
    string edge_input;
    char pinput = ' ';

    while (getline(cin, line)) {
        istringstream input(line);
        while (input >> u_input) {
            u_input=(toupper(u_input));
	    try
	    {
            switch (u_input)
            {
                case 'V' :
                    if (pinput == 'V')
                    {
                        cerr << "Error: V must be followed by E only.\n";
                        break;
                    }
                    else
                    {
                        input >> no_v;

			if(no_v <= 0)
				{
					throw " Invalid number of vertices ";
				}	
				
                        graph_input.init(no_v); // initialise graph
                        pinput = 'V';
                        break;
                    }

                case 'E' :
                {
                    unsigned int fle = 0;
                    if (pinput == 'E')
                    {
                        cerr << "Error: V and E always occur together.\n ";
                        break;
                    }
                    else
                    {
                        input >> edge_input;
                        istringstream input_edg(edge_input);
                        unsigned int elem_v = 0, v1, v2;
                        char edge_ch;

                        input_edg >> edge_ch;

                        while (edge_ch != '}') {
                            input_edg >> edge_ch;
                            if (edge_ch == '}')
                            {
                                fle = 1;
                                break;
                            }
                            else
                            {
                                input_edg >> elem_v;
                                v1 = elem_v;
                                input_edg >> edge_ch;
                                input_edg >> elem_v;
                                v2 = elem_v;

                                input_edg >> edge_ch;
                                input_edg >> edge_ch;
                                if (v1 >= no_v || v2 >= no_v)
                                {
                                    cerr << "Error: Vertex out of range.\n";
				    graph_input.adjacency_l.clear();
                                    break;
                                }
                                graph_input.add({v1,v2});
                            }
                        }
                        if(fle == 1)
                        {
                            pinput = 'E';
                            break;
                        }
                        minimum_vertexcover(graph_input);
                        pinput = 'E';
                        break;

                    }
                }

            }
}
		catch (const char* err) {
                cerr << "Error:" << err << endl;
		}
        }
    }
return 0;
}
