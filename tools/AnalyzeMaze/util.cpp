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
#include "util.hpp"

#define fabs abs

double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

double diffi( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return 2*((dx1*dx1 + dy1*dy1)-(dx2*dx2 + dy2*dy2) + 1e-10)/(dx1*dx1 + dy1*dy1 + dx2*dx2 + dy2*dy2);
}

ostream& operator <<(ostream& os, ContourSet& con){
    os <<"Contours:"<<endl;
    for (ContourSet::iterator i = con.begin(); i != con.end(); i++){
        os <<*i<<endl;
    }
    os <<endl;
    os <<"end of Contours"<<endl;
    return os;
}

#define SEQ_DEVIATION 225
void testClassification(vector<ContourSet>& similarContours){
    cout <<"test classifycation"<<endl;
    for (vector<ContourSet>::iterator i = similarContours.begin();
         i != similarContours.end(); i++){
         cout <<*i<<endl;
        //Mat test = testc.clone();
        //drawContours(test, *i, -1, Scalar(0,255,0));
        //imshow("test", test);
        //waitKey(0);
    }
    //cout <<"similarContours.size()="<<similarContours.size()<<endl;
}
//end

void classifySimilarContours(ContourSet& s, vector<ContourSet>& similarContours){
    similarContours.clear();
    for (ContourSet::iterator i = s.begin(); i != s.end(); i++){
        Point& anchori = (*i).front();
        vector<ContourSet>::iterator j;
        for (j = similarContours.begin(); j != similarContours.end(); j++){
            Point& anchorj = (*j).front().front(),delta = anchori - anchorj;
            double areai= contourArea(*i), areaj = contourArea((*j).front());
            if (delta.x*delta.x + delta.y*delta.y < SEQ_DEVIATION
                && ((areai-areaj)*2/(areai+areaj))<0.1){
                    //(*j).push_back(*i);
                    break;
                }
        }
        //cout <<*i<<endl;
        if (j != similarContours.end())
            (*j).push_back(*i);
        else{
            similarContours.push_back(vector<Contour>(1,*i));
        }
    }
}

void simplifyContours(vector<ContourSet>& similar, ContourSet& s){
    s.clear();
    for (vector<ContourSet>::iterator i = similar.begin(); i != similar.end(); i++){
        ContourSet::iterator j = (*i).begin();
        //if there are 2 main maze contour(outer contour), take the smaller one
        //sub maze coutours are inner contours
        if (i == similar.begin() && (*i).size() > 1 &&
            fabs(contourArea((*i)[0])) > fabs(contourArea((*i)[1]))){
            // cout <<"area 0="<<contourArea((*i)[0])<<"area 1="<<contourArea((*i)[1])<<endl;
            j++;
        }
        
        if (j == (*i).end())
            continue;
        Point pp = (*j).front();
        double x1 = pp.x, x2 = pp.x, y1 = pp.y, y2 = pp.y;  
        // cout <<"contour ="<<(*j)<<endl;
        for (Contour::iterator k = (*j).begin(); k != (*j).end(); k++){
            x1 = MIN((*k).x, x1);
            x2 = MAX((*k).x, x2);
            y1 = MIN((*k).y, y1);
            y2 = MAX((*k).y, y2);
            // x1 = MAX((*k).x, x1);
            // x2 = MIN((*k).x, x2);
            // y1 = MAX((*k).y, y1);
            // y2 = MIN((*k).y, y2);
        }

        Contour c;
        c.push_back(Point(x1+1,y1+1));
        c.push_back(Point(x1+1,y2-1));
        c.push_back(Point(x2-1,y2-1));
        c.push_back(Point(x2-1,y1+1));
        // cout <<"push :"<<c<<endl;
        s.push_back(c);
    }
    // cout <<"simplified s="<<s<<endl;
}

#define CONTOUR_LOC_ERR 30
bool contourLocationLessThan(const Contour& i,const  Contour& j){
    Point pi = i.front(), pj = j.front();
    return fabs(pi.y-pj.y) < CONTOUR_LOC_ERR ?(pi.x<pj.x?true:false):(pi.y<pj.y?true:false);
}

void removeRedundantContour(ContourSet& s){
    vector<ContourSet> similarContours;
    // cout <<"removeRedundantSeq"<<endl;

    //classify similar contours
    classifySimilarContours(s,similarContours);
    // testClassification(similarContours);

    simplifyContours(similarContours, s);

    classifySimilarContours(s,similarContours);
    simplifyContours(similarContours, s);

    // classifySimilarContours(s,similarContours);
    // testClassification(similarContours);

    sort(s.begin(), s.end(), contourLocationLessThan);
}

void drawContour(ContourSet& s, Mat& img){
    for( size_t i = 0; i < s.size(); i++ )
    {
        const Point* p = &s[i][0];
        int n = (int)s[i].size();
        polylines(img, &p, &n, 1, true, Scalar(0,255,0), 3, CV_AA);
    }
}

template <class _T, class _t>
inline bool sameP(_T& i, _t& j, int deviation=5){
    return fabs(i.x - j.x) < deviation && fabs(i.y - j.y) < deviation ;
}

void classifyPoints(vector<Point>&ps, vector<vector<Point> >& cps){
    cps.clear();
    for( vector<Point>::iterator i = ps.begin(); i != ps.end(); i++){
        vector<vector<Point> >:: iterator j = cps.begin();
        for (; j != cps.end(); j++){
            if (sameP(*i, (*j).front(), dotPitchDeviation)){
                (*j).push_back(*i);
                break;
            }
        }
        if (j != cps.end())
            continue;
        cps.push_back(vector<Point>(1, *i));
    }
}

void removeRedundantP(vector<Point>& points){
    vector<vector<Point> > tmp;
    classifyPoints(points, tmp);
    //simplify
    points.clear();
    for (vector<vector<Point> >::iterator i = tmp.begin();
         i != tmp.end(); i++){
        //points.push_back(1/(*i).size() * accumulate((*i).begin(), (*i).end(), Point()));
        //points.push_back(accumulate((*i).begin(), (*i).end(), Point(0, 0)));
        points.push_back((*i).front());
    }
}

bool dotLocationLessThan(const Point& pi,const Point& pj){
    return fabs(pi.y-pj.y) < dotPitchDeviation ?(pi.x<pj.x?true:false):(pi.y<pj.y?true:false);
}

void findPinFP( vector<Point2f>& src, vector<Point>& dst, Contour& matchContour){
    for (vector<Point2f>::iterator i = src.begin();
         i != src.end(); i++){
        double dotLineDistance = pointPolygonTest(matchContour, *i, true);
        bool contourCorner = false;
        for (Contour::iterator j = matchContour.begin();
             j != matchContour.end(); j++){
            if (sameP(*i, *j, 2*dotLineDeviation)){
                contourCorner = true;
                break;
            }
        }
        if (fabs(dotLineDistance) > dotLineDeviation || contourCorner){
            continue;
        }
        dst.push_back(*i);
    }
    removeRedundantP(dst);
    sort(dst.begin(), dst.end(), dotLocationLessThan);
}

int getGrayLevel(Mat& img,const Point& p){
    const uchar* row = img.ptr<uchar>(p.y);
    return (int)row[p.x];
}

void drawPoint(Mat& img, const Point& point, char color){
    circle (img, point, 2, Scalar(color=='B'?255:0,color=='G'?255:0,color=='R'?255:0), -1, 8);
}

#define CONTRACT_STEP 5
Point contractCorr(int seq, float level){
    switch(seq){
    case 0:
        return Point(level*CONTRACT_STEP, level*CONTRACT_STEP);
    case 1:
        return Point(level*CONTRACT_STEP, -level*CONTRACT_STEP);
    case 2:
        return Point(-level*CONTRACT_STEP, -level*CONTRACT_STEP);
    case 3:
        return Point(-level*CONTRACT_STEP, level*CONTRACT_STEP);
    }
    return Point(0,0);
}

void calculatePin(vector<Point>& pin){
    vector<Point> tmp = pin;
    pin.clear();
    for (vector<Point>::iterator i = tmp.begin(), j=i ; i != tmp.end(); i = ++j){
        j++;
        pin.push_back(((*i)+(*j))*0.5);
    }
}

string calculateName(int pos){
    return string("PABCDEFGHIJKLMN", pos, 1);
}

bool isOrthoContour(Contour& c, double error){
    double maxCosine = 0;
    int size = c.size();

    for( int j = 2; j < size + 2; j++ )
    {
        // find the maximum cosine of the angle between joint edges
        double cosine = fabs(angle(c[j%size], c[j-2], c[(j-1)%size]));
        maxCosine = MAX(maxCosine, cosine);
    }

    // if cosines of all angles are small
    // (all angles are ~90 degree) then write quandrange
    // vertices to resultant sequence
    if( maxCosine > error )//<5% diviation, cos(90*0.95)=0.0784
        return false;
    
    return true;
}

bool isSquareContour(Contour& c, double error){
    double maxDiff = 0;
    for( int j = 2; j < 5; j++ ){
        double diff = fabs(diffi(c[j%4], c[j-2], c[j-1]));
        maxDiff = MAX(maxDiff, diff);
    }
    if (maxDiff > error)
        return false;

    return true;
}

bool findGrayBreak(Mat& bin, LineIterator& it, Point& end){
    int preScale = getGrayLevel(bin, it.pos()), thisScale;
    for (; it.pos() != end; it++){
        thisScale = getGrayLevel(bin, it.pos());
        //cout <<" thisScale="<<thisScale<<" ";
        if (thisScale != preScale){//color edge
            //cout <<"find"<<it.pos()<<" ";
            return true;
        }
        preScale = thisScale;
    }
    return false;
}

Point findGrayBreak(Mat& bin, Point start, Point& step){
    Point end = start;
    end.x = step.x?(step.x<0?0:bin.cols):end.x;
    end.y = step.y?(step.y<0?0:bin.rows):end.y;
    LineIterator it(bin, start, end, 4);
    if (findGrayBreak(bin, it, end))
        return it.pos();
    return start;
}

#define ESTIMATION_BORDER_AND_MAINPIN 50
//int getLineWidth(Mat& bin, vector<vector<Point> >&pSet){
int getInfo(Mat& bin, int& wireWidth, int& widthOfBorderAndPin){
    for (int step = ESTIMATION_BORDER_AND_MAINPIN; step >=0; step-=1){
        vector<int> tmpDist;
        // Point start = pSet.front().front() + Point(step, step);
        // Point end = pSet.front().back() + Point(-step, step);
        Point start = Point(step, step);
        Point end = Point(bin.cols - step, step);
        LineIterator it(bin, start, end, 8);
        findGrayBreak(bin, it, end);
        Point p1 = it.pos(), p2;
        for (; findGrayBreak(bin, it, end); p1 = it.pos()){
            p2 = it.pos();
            tmpDist.push_back(fabs(p2.x-p1.x));
            if (!findGrayBreak(bin, it, end))
                break;
        }
        if (!tmpDist.size())
            continue;
        sort(tmpDist.begin(),tmpDist.end());
        int thisDist = tmpDist.front();
        if (!wireWidth)
            wireWidth = thisDist;
        if (!widthOfBorderAndPin && thisDist > wireWidth){
            widthOfBorderAndPin = start.y;
            //cout <<"wireWidth="<<wireWidth<<"widthOfBorderAndPin="<<widthOfBorderAndPin<<endl;
            return 0;
        }
    }
    return -1;
}

int erodeWire(Mat& bin, int width){
    int radius = (width + 1)/2;
    Mat element = getStructuringElement(MORPH_CROSS, Size(2*radius+1, 2*radius+1), Point(radius,radius) );
    Mat tmp;
    erode(bin, tmp, element);
    dilate(tmp, bin, element);
    return 0;
}

bool isSubContour(Contour& son, Contour& parent){
    for (Contour::iterator i = son.begin(); i != son.end(); i++){
        double dist = pointPolygonTest(parent, *i, true);
        if (dist <0)
            return false;
    }
    return true;
}

void contourRoi2base(Contour& c, Point anchor){
    for (Contour::iterator i = c.begin(); i != c.end(); i++)
        *i += anchor;
}

bool closelyRegular(Contour& c, float th){
    vector<float> dist2;
    vector<Point> v;
    for (int i = 1; i < c.size() + 1; i++)
        v.push_back(c[i % c.size()] - c[i-1]);
    for (int i = 0; i < v.size(); i++)
        dist2.push_back(v[i].x*v[i].x + v[i].y*v[i].y);
    sort(dist2.begin(),dist2.end());
    return dist2.front()/dist2.back() >= th;
}

Point getDirection(vector<Point>& m, int seq){
    switch(4*seq/m.size()){
    case 0:
        return Point(1,0);
    case 1:
        return Point(0,-1);
    case 2:
        return Point(-1,0);
    case 3:
        return Point(0,1);
    }
    return Point(1,0);
}

char getColor(Mat& img, Point& pin){
    int b = (int)img.at<Vec3b>(pin.y,pin.x)[0];
    int g = (int)img.at<Vec3b>(pin.y,pin.x)[1];
    int r = (int)img.at<Vec3b>(pin.y,pin.x)[2];
    //cout <<"b="<<b<<"g="<<g<<"r="<<r<<endl;
    if (b > 160 && g > 160 && r > 160)
        return 'W';
    if (b < 60 && g < 60 && r < 60)
        return 'D';//dark..
    int m = MAX(b, g);
    m = MAX(m, r);
    if (b == m)
        return 'B';
    if (g == m)
        return 'G';
    if (r == m)
        return 'R';
    return 0;
}

Point findColorBreak(Mat& img, Point p, Point& step){
    //cout <<"init pin="<<pin<<"step="<<step<<endl;
    for (char c1 = getColor(img, p), c2=c1;
         c2 == c1;){
        p += step;
        c2 = getColor(img,p);
        //cout <<"c1="<<c1<<"c2="<<c2<<"next pin="<<pin<<endl;
    }
    return p;
}

ostream& operator <<(ostream& os, list<PointAndStep>& l){
    os <<"list:"<<endl;
    for (list<PointAndStep>::iterator i = l.begin(); i != l.end(); i++){
        os <<"Point="<<(*i).first<<"step="<<(*i).second<<endl;
    }
    os <<endl;
    os <<"end of list"<<endl;
    return os;
}

ostream& operator <<(ostream& os, set<string>& ss){
    for (set<string>::iterator i = ss.begin(); i != ss.end(); i++){
        os <<(i!=ss.begin()?" ":"")<<*i;
    }
    os <<endl;
    return os;
}

string operator +(string& s, int i){
    stringstream out;
    out << s<<i;
    return out.str();
}

#define sign(num) ((num)<0?-1:(num)>0?1:0)
Point getNextStep(Point step, int seq){
    //calculate rotation angle
    int beta = seq - 2;
    int sine = sign(beta), cosine = sign(2 - fabs(beta));
    //double sine = sin(beta*CV_PI/4), cosine= cos(beta*CV_PI/4);
    //calculate direction by rotation angle and original step vector
    //Point p(step.x*signCos - step.y*signSin, step.y*signCos+ step.x*signSin);
    Point p(step.x*cosine - step.y*sine, step.y*cosine+ step.x*sine);
    if (step.x *2 == p.x)
        p.x = step.x;
    if (step.y *2 == p.y)
        p.y = step.y;
    return p;
}

Point findLineMiddle(Mat& bin, Point p, Point& step){
    Point end1 = p + step * 1.2, end2 = p - step * 1.2;
    Point p1, p2;
    LineIterator it1 (bin, p, end1, 8);
    if (findGrayBreak(bin, it1, end1))
        p1 = it1.pos();
    else
        return p;
    LineIterator it2 (bin, p, end2, 8);
    if (findGrayBreak(bin, it2, end2))
        p2 = it2.pos();
    else
        return p;
    return (p1 + p2)*0.5;
}

