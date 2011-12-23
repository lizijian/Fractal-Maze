#ifndef __SCAN_MAZE__
#define __SCAN_MAZE__
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <list>
#include <set>


using namespace cv;
using namespace std;

#define Contour vector<Point>
#define ContourSet vector<vector<Point> >
#define PointAndStep pair<Point, Point>
#define Connections vector<set<string> >

#define TYPE_GRAY 1
#define TYPE_COLOR 2

class ScanMaze{
public:
    ScanMaze(string name);
    ~ScanMaze();
    int analyze();
    int displaySubMaze();
    int displayPins();
    int displayPoles();
    int displayConnections();
    int save(string path = string());
private:
    //internal sub function
    int detectSubMaze();
    int detectPin();
    int detectPoles();
    int detectConnections();
    //auxillary function
    int trackWire(Mat& img, Point& src, set<string>& dsts, Point& direction);
    int checkPossibleNextC(Mat& img, list<PointAndStep>& q,int thisColor);
    int checkPossibleNextG(Mat& img, list<PointAndStep>& q);
    bool onBorder(Point& p, float err);
    string locatePin(Point& p);

    ////image information
    string srcFileName;
    //original , gray and binary image
    Mat image, grayImg, binImg;
    //image type, gray or colored
    int type;
    //attrs
    int wireWidth, widthOfBorderAndPin;
    
    ////some settings
    int numPin, resolution;

    ////abstract infomation through analysis
    ContourSet subMazeContour,potentialPoles,junctionPoints;
    //poles contour
    Contour cathode, anode;
    //detected pin set, main = 0, sub maze = 1,2...
    vector<vector<Point> > pinSet;
    //name of maze, main = P, sub=A,B,C...
    vector<string> nameSet;
    //set of equipotential pins
    Connections connections;
};

extern bool debug;
extern int dotPitchDeviation;
extern int dotLineDeviation;
#endif
