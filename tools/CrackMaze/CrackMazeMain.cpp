#include "CrackMaze.hpp"
#include <unistd.h>
#include <stdio.h>

extern char *optarg;

void usage(){
    cout <<"usage: CrackMaze -f <FILE>"<<endl;
    cout <<"        -f <FILE>           File of analysis result."<<endl;
}

int main(int argc, char** argv){
    char* path=NULL;
    bool debug = false;
    char opt;
    while((opt = getopt(argc, argv, "f:d")) != -1)
        switch(opt){
        case 'f':
            path = optarg;
            continue;
        case 'd':
            debug = true;
            continue;
        }
    
    if (!path){
        cout <<"Path to a fractal maze strucure file is required."<<endl<<endl;
        usage();
        return -1;
    }

    chip maze(0, path);

    if (debug)
        maze.displayConn();
    maze.crack();
    return 0;
}
