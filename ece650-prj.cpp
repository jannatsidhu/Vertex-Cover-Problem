#include "graph.h"
#include "avc1.h"
#include "avc2.h"
#include "minvc.h"
#include <pthread.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <memory>
#include <unistd.h>
#include <ctime>

using namespace std;

static void *(* algorithm[])(void *) = {APPROX_VC_3, APPROX_VC_1, APPROX_VC_2};
static const char *names_gr[] = {"CNF-SAT-VC: ", "APPROX-VC-1: ", "APPROX-VC-2: "};

void run_algorithm(Graph_struct &graph)
{
    pthread_t thread_no[3];
    vector_vertices *cov_op[3];
    int pth_ret;
    for(size_t i = 0; i < 3;++i) {
        pth_ret = pthread_create(&thread_no[i], nullptr, algorithm[i], &graph);
        if (pth_ret)
        { 
            std::cout<<"Error: pthread error occured";
            exit(1);
        }
    }

    for(size_t i = 0; i < 3;++i) {
        pthread_join(thread_no[i], (void **)&cov_op[i]);
        cout << names_gr[i];
        if(!cov_op[i]) continue;
        vector_vertices &C = *cov_op[i];

        for (unsigned k=0; k < C.size(); k++){
            cout<<C[k];
            if(k + 1 != C.size()){
                cout<<',';
            }
        }
        cout << endl;
    }

    for(size_t l = 0; l < 3; ++l) {
        delete(cov_op[l]);
    }

}

void *du_iothread(void *){
    Graph_struct &graph = *new Graph_struct();
    char command, pre_command = '0';
    string e_string, line;
    unsigned int num_of_vertex = 0;

    while (getline(cin, line)) {
        istringstream input(line);
        while (input >> command) {
            switch (command)
            {
                case 'V' :
                    if (pre_command == 'V')
                    {
                        cerr << "Error: Repetition of first character.\n";
                        break;
                    }
                    else
                    {
                        input >> num_of_vertex;
                        graph.init(num_of_vertex);
                        pre_command = 'V';
                        break;
                    }

                case 'E' :
                {
                    unsigned int precmd_f = 0;
                    if (pre_command == 'E')
                    {
                        cerr << "Error: Repetition of first character.\n ";
                        break;
                    }
                    else
                    {
                        input >> e_string;
                        istringstream input_edg(e_string);
                        char e_char;
                        unsigned int v_elem = 0, v1,v2;
                        input_edg >> e_char;//read '{'

                        while (e_char != '}') {
                            input_edg >> e_char;// read '<'
                            if (e_char == '}')
                            {
                                precmd_f = 1;
                                break;
                            }
                            else
                            {

                                input_edg >> v_elem;// read the first vertex
                                v1 = v_elem;
                                input_edg >> e_char;// read ','
                                input_edg >> v_elem;// read the second vertex
                                v2 = v_elem;
                                input_edg >> e_char;// read '>'
                                input_edg >> e_char;// read ',' or '}'

                                graph.add({v1,v2});
                                if (v1 > num_of_vertex || v2 > num_of_vertex)
                                {
                                    cerr << "Error: Co-ord order is OUT OF RANGE!\n";
                                    break;
                                }

                            }

                        }
                        if(precmd_f == 1)
                        {
                            pre_command = 'E';
                            break;
                        }
                        run_algorithm(graph);
                        pre_command = 'E';
                        break;

                    }
                }

            }

        }

    }
    return nullptr;
}

int main(int argc, char **argv)
{
    int pth_ret;
    pthread_t io_thread;
    srand(time(nullptr));
    pth_ret = pthread_create(&io_thread, nullptr, du_iothread, nullptr);
    if (pth_ret) return 1;
    pthread_join(io_thread, NULL);
    pthread_exit(0);
    return 1;
}















