#include "scanMaze.hpp"
#include <unistd.h>

extern char *optarg;
extern bool debug;
int main(int argc, char** argv){
    string srcFile;
    string resultPath;
    char opt;
    while((opt = getopt(argc, argv, "f:t:d")) != -1)
        switch(opt){
        case 'f':
            srcFile = optarg;
            continue;
        case 't':
            resultPath = optarg;
            continue;
        case 'd':
            debug = true;
            continue;
        } 
    if (srcFile.empty()){
        cout <<"Path to a fractal maze image is required."<<endl<<endl;
        cout <<"usage: AnalyzeMaze -f <FILE> [-t <result files path> -d]"<<endl;
        cout <<"-f    :path to source image."<<endl;
        cout <<"-t    :where to save taget files."<<endl;
        cout <<"-d    :turn on debug"<<endl;
        return -1;
    }

    ScanMaze maze(srcFile);
    maze.analyze();
    maze.save(resultPath);
    return 0;
}
