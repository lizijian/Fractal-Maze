#ifndef __SCAN_MAZE_UTIL__
#define __SCAN_MAZE_UTIL__
#include "scanMaze.hpp"
// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
double angle( Point pt1, Point pt2, Point pt0 );
//calculate diviation between pt0-pt1 and pt0-pt2
double diffi( Point pt1, Point pt2, Point pt0 );
ostream& operator <<(ostream& os, ContourSet& con);
void testClassification(vector<ContourSet>& similarContours);
//classify ContourSet s
void classifySimilarContours(ContourSet& s, vector<ContourSet>& similarContours);
//simplify similar contours, calculate 1 Contour from each similar
//group(element of similar) and save ContourSet s.
void simplifyContours(vector<ContourSet>& similar, ContourSet& s);
//remove redundant contour from s, eg:[0,0; 100,0; 100,100; 0,100] and
//[0,1; 100,1; 100,101; 0,101]
void removeRedundantContour(ContourSet& s);
//draw points
template <class _T>
void drawPoints(Mat& img, vector<_T>& points, char color){
    for (int i = 0; i < points.size(); i++){
        circle (img, points[i], 3, Scalar(color=='B'?255:0,color=='G'?255:0,color=='R'?255:0), -1, 8);
    }
}

void drawPoint(Mat& img, const Point& point, char color);

void drawContour(ContourSet& s, Mat& img);
//find Pin points which is matched with given contour line
void findPinFP( vector<Point2f>& src, vector<Point>& dst, Contour& matchContour);
//get gray level from a CV_8U image
int getGrayLevel(Mat& img,const Point& y);
//correction to contract maze contour gradually to detect pin/subpin
//because sometimes the detected contour is outside contour and
//can not detect pin/subpin
Point contractCorr(int seq, float level);
//calculate pin/name for detected pin point
void calculatePin(vector<Point>& pin);
string calculateName(int pos);
//if every corner of contour is right angle 
bool isOrthoContour(Contour& c, double error);
bool isSquareContour(Contour& c, double error);
//
bool findGrayBreak(Mat& bin, LineIterator& it, Point& end);
Point findGrayBreak(Mat& bin, Point start, Point& step);
//
int getInfo(Mat& bin, int& wireWidth, int& widthOfBorderAndPin);
int erodeWire(Mat& bin, int width);
bool isSubContour(Contour& son, Contour& parent);
void contourRoi2base(Contour& c, Point anchor);
//if contour is approximately regular polygon
bool closelyRegular(Contour& c, float th);
//calculate direction by sequence of pin point
Point getDirection(vector<Point>& m, int seq);
//calculate next step by sequence
Point getNextStep(Point step, int seq);
char getColor(Mat& img, Point& pin);
Point findColorBreak(Mat& img, Point p, Point& step);
ostream& operator <<(ostream& os, list<PointAndStep>& l);
ostream& operator <<(ostream& os, set<string>& ss);
string operator +(string& s, int i);
Point findLineMiddle(Mat& bin, Point p, Point& step);
#endif
