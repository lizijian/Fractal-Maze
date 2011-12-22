//    This file is part of Fractal Maze.
//
//    Foobar is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Fractal Maze is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
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
