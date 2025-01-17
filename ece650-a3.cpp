// inspired by the programs posted by PROF on github i.e using_exec.cpp, using_pipe.cpp, using_rand.cpp, using_getopt.cpp

#include <iostream>
#include<unistd.h>
#include "signal.h"
#include "sys/wait.h"

int sendinputtoa2()
{
    while(!std::cin.eof()){
        std::string line;
        std::getline(std::cin, line);
        std::cout<<line<<std::endl;
    }
    return 0;
}

int main(int argc,char **argv) {

    int status;
    int pipefromRgentoA1[2];
    pipe(pipefromRgentoA1);
    int pipefromA1toA2[2];
    pipe(pipefromA1toA2);

    pid_t Rgenprocessid = fork();
    if(Rgenprocessid == 0){
        //only Rgen here
        dup2(pipefromRgentoA1[1],STDOUT_FILENO);//redirect std output of Rgen to pipe
        close(pipefromRgentoA1[0]);//close old read write ends
        close(pipefromRgentoA1[1]);
        execv("./rgen",argv); // so that the forked process now startes running as a concurrent process separate from parent
    }
    else{
        pid_t a1processid = fork();
        if( a1processid == 0){
            //only a1 here
            char *argv1[3];
            argv1[0] = (char *)"python";
            argv1[1] = (char *)"ece650-a1.py";
            argv1[2] = nullptr;

            dup2(pipefromRgentoA1[0],STDIN_FILENO); //redirect std input from pipe
            close(pipefromRgentoA1[0]); close(pipefromRgentoA1[1]);

            dup2(pipefromA1toA2[1], STDOUT_FILENO);
            close(pipefromA1toA2[0]); close(pipefromA1toA2[1]);
            execvp("python", argv1);
        }
        else{
            pid_t a2processid = fork();
            if (a2processid == 0){
                //only a2 here
                dup2(pipefromA1toA2[0],STDIN_FILENO);
                close(pipefromA1toA2[0]); close(pipefromA1toA2[1]);
                execv("./ece650-a2", argv);
            }
            // only parent process i.e a3 runs this
            dup2(pipefromA1toA2[1],STDOUT_FILENO);// std output is redirected to pipe so that a2 can recieve shortest path queries
            close(pipefromA1toA2[0]); close(pipefromA1toA2[1]);
            int res=sendinputtoa2(); // teh parent process that runs in parallel will send input to a2

            kill(Rgenprocessid, SIGTERM);
            waitpid(Rgenprocessid, &status, 0);
            kill(a1processid,SIGTERM);
            waitpid(a1processid, &status, 0);
            kill(a2processid,SIGTERM);
            waitpid(a2processid, &status, 0);

            return res;
        }
    }


}

//
// Created by Jannat Sidhu on 2019-11-03.
//
