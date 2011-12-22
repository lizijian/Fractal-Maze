#include "scanMaze.hpp"
#include "util.hpp"

#define MAX_COUNT 500

int dotLineDeviation = 5;
int dotPitchDeviation = 5;
bool debug = false;

ScanMaze::ScanMaze(string name){
    image = imread(name, 1);
    if (image.empty()){
        cout <<"Can not load "<<name<<endl;
        exit (-1);
    }
    
    //init
    wireWidth = 0;
    widthOfBorderAndPin = 0;
    numPin = 0;

    //default options
    resolution = 40;

    Mat gray(image.size(), CV_8U);
    cvtColor(image, gray, CV_BGR2GRAY);
    binImg = gray < 160;
    gray.copyTo(grayImg);
    getInfo(binImg, wireWidth, widthOfBorderAndPin);

    //if image is colored
    Mat tmp;
    cvtColor(gray, tmp, CV_GRAY2BGR);
    Mat tmp1 = (image-tmp)(Range(10,tmp.cols-10),Range(10,tmp.rows-10)), tmp2;
    cvtColor(tmp1, tmp2, CV_BGR2GRAY);
    Mat tmp3 = tmp2 > 20;
    type = countNonZero(tmp3)?TYPE_COLOR:TYPE_GRAY;

    //get src filename(no path)
    string file = name;
    size_t  found = file.find_last_of("/\\");
    srcFileName = file.substr(found+1);
}

ScanMaze::~ScanMaze(){
}

int ScanMaze::analyze(){
    detectSubMaze();
    detectPin();
    detectPoles();
    if (debug){
        displaySubMaze();
        displayPoles();
        displayPins();
    }
    detectConnections();
    //if (debug)
        //displayConnections();
    return 0;
}

int ScanMaze::save(string path){
    ofstream *ana = NULL, *loc = NULL;
    string result = path + "\\" + srcFileName;
    if (!path.empty()){
        ana = new ofstream;
        ana->open((result + ".ana").c_str());
        if (!ana->is_open())
            cout <<"Can not open["<<result+".ana"<<"], switch to stdout."<<endl;
        loc = new ofstream;
        loc->open((result + ".loc").c_str());
        if (!loc->is_open())
            cout <<"Can not open["<<result+".loc"<<"], switch to stdout."<<endl;
    }
    ostream& ana1 = ana&&ana->is_open()?*ana:cout;
    ostream& loc1 = loc&&loc->is_open()?*loc:cout;
    
    if (loc1 == cout)
        cout <<endl<<"Location:"<<endl;

    for (int i = 0; i < pinSet.size(); i++){
        for (int j = 0; j < pinSet[i].size(); j++){
            loc1 <<nameSet[i]+j<<" "<<pinSet[i][j]<<endl;
        }
    }

    if (ana1 == cout)
        cout <<endl<<"Analysis result:"<<endl;
    
    for (Connections::iterator i = connections.begin();
         i != connections.end(); i++)
        ana1 << *i;

    if (ana)
        ana->close();
    if (loc)
        loc->close();
    return 0;
}

int ScanMaze::detectSubMaze(){
    subMazeContour.clear();
    ContourSet contours;
    Mat bin = binImg.clone();
    // vector<Vec4i> hierarchy;
    
    // find contours and store them all as a list
    findContours(bin, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    // findContours(bin, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

    vector<Point> approx;
    int area;
    // test each contour
    for( size_t i = 0; i < contours.size(); i++ )
    {
        // approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

        // square contours should have 4 vertices after approximation
        // relatively large area (to filter out noisy contours)
        // and be convex.
        // Note: absolute value of an area is used because
        // area may be positive or negative - in accordance with the
        // contour orientation
        area = fabs(contourArea(Mat(approx)));
        if( approx.size() == 4 && isContourConvex(Mat(approx))){
            if (area > 1000)
            {
                //is rectangle
                if (!isOrthoContour(approx, 0.077)) //error limit:0.077= cos(85.5),4.5 degree = 5%*90
                    continue;
                
                if (!closelyRegular(approx, 0.9))
                    continue;
                
                subMazeContour.push_back(approx);
            }else{
                //10% error=> cos(80) = 0.098, because cathode is relatively small
                if (!isOrthoContour(approx, 0.098))
                    continue;

                potentialPoles.push_back(approx);
            }
        }
        //find anode, !4 corner(12corner)
        if (approx.size() == 12){
            if (!isOrthoContour(approx, 0.098))
                continue;
            
            potentialPoles.push_back(approx);
        }
        //find potential cross point contour
        if(area < 16 //small
           && approx.size()>3 //not 2d
           && closelyRegular(approx, 0.5) //more regular rather than long and narrow
            ){
            crossPoints.push_back(approx);   
        }
    }
    removeRedundantContour(subMazeContour);
    return 0;
}

#define SM "Sub Maze"
int ScanMaze::displaySubMaze(){
    namedWindow(SM, 1);
    Mat img=image.clone();
    drawContour(subMazeContour, img);
    imshow(SM, img);
    waitKey(0);
    destroyWindow(SM);
    return 0;
}

#define PINS "finded pins"
int ScanMaze::displayPins(){
    Mat pin;
    cvtColor(grayImg, pin, CV_GRAY2BGR);
    namedWindow(PINS, 1);
    for (int i = 0; i < pinSet.size(); i++){
        for (int j = 0; j < pinSet[i].size(); j++){
            drawPoint(pin, pinSet[i][j], 'R');
        }
    }
    imshow(PINS, pin);
    waitKey(0);
    destroyWindow(PINS);
    return 0;
}

int ScanMaze::detectPin(){
    ////calculate pin point and name
    vector<Point> rawPinPoints;//1pin detect 2 points
    int pos;
    ContourSet::iterator c;
    for ( c = subMazeContour.begin(), pos = 0;
         c != subMazeContour.end(); c++, pos++){//each maze contour
        for (int level = 0; level < 3; level++){//3 levels' correction to contract contour
            rawPinPoints.clear();
            for (int seq = 0; seq < 4; seq++){//4 edges
                Point start = (*c)[seq] + contractCorr(seq, level);
                Point end =(*c)[(seq+1)%4] + contractCorr((seq+1)%4, level);
                LineIterator it(binImg, start, end, 8);
                int size1 = rawPinPoints.size();
                for (;findGrayBreak(binImg, it, end);rawPinPoints.push_back(it.pos()))
                    ;
                int size2 = rawPinPoints.size();
                if (size1 == size2)
                    break;
            }
            if (rawPinPoints.size()){//result of detection is correct
                if (!numPin)
                    numPin = rawPinPoints.size();
                break;
            }
        }
        //calculate pin and restore result
        calculatePin(rawPinPoints);//results in rawPinPoints
        //XXX: simple way is calculating name by sequence
        //better method is detecting character from image.future function.
        string name = calculateName(pos);
        pinSet.push_back(rawPinPoints);
        nameSet.push_back(name);
    }
    return 0;
}

bool areaMoreThan(pair<int, int> i, pair<int, int> j){
    return i.first > j.first;
}

#define DPOLES "detect poles"
int ScanMaze::detectPoles(){
    Mat poles = binImg.clone();

    //erode wire and exclude main maze border and main pins
    erodeWire(poles, wireWidth);

    Mat roi = poles(Range(widthOfBorderAndPin, poles.cols - widthOfBorderAndPin),
                    Range(widthOfBorderAndPin, poles.rows - widthOfBorderAndPin));

    //sort: 2 pole base contours are bigger than others
    ContourSet contours;
    findContours(roi, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    vector<pair<int, int> > area2index;
    for (int i = 0; i < contours.size(); i++){
        area2index.push_back(pair<int, int>(contourArea(contours[i]), i));
    }
    sort (area2index.begin(), area2index.end(), areaMoreThan);
    

    //convert ROI contours to original binary contours
    Point anchor;
    Size wholeSize;
    roi.locateROI(wholeSize, anchor);
    for (int i = 0; i < area2index.size() && i < 2; i++){
        contourRoi2base(contours[area2index[i].second], anchor);

        // approxPolyDP(Mat(contours[area2index[i].second]), approx,
        //              arcLength(Mat(contours[area2index[i].second]), true)*0.02, true);
        
        // contourApprox.push_back(approx);
    }

    //find out poles
    for (ContourSet::iterator i = potentialPoles.begin();
         i != potentialPoles.end(); i++){
        for (int j = 0; j < 2; j++){
            if (isSubContour((*i), contours[area2index[j].second])){
                if ((*i).size() == 4){
                    cathode = contours[area2index[j].second];
                }else{
                    anode = contours[area2index[j].second];
                }
            }
        }
    }
    return 0;
}

int ScanMaze::displayPoles(){
    Mat tmp = image.clone();
    namedWindow(DPOLES,1);
    drawPoints(tmp, cathode, 'G');
    drawPoints(tmp, anode, 'R');
    imshow(DPOLES, tmp);
    waitKey(0);
    destroyWindow(DPOLES);
    return 0;
}

bool ScanMaze::onBorder(Point& p, float err){
    if (err >fabs(pointPolygonTest(cathode, p, true)))
        return true;
    if (err >fabs(pointPolygonTest(anode, p, true)))
        return true;
    for (int i = 0; i < subMazeContour.size(); i++){
        if (err >fabs(pointPolygonTest(subMazeContour[i], p, true)))
            return true;
    }
    return false;
}

string ScanMaze::locatePin(Point& p){
    if (pointPolygonTest(cathode, p, true) >= 0)
        return "Cathode";
    if (pointPolygonTest(anode, p, true) >= 0)
        return "Anode";
    double dist = 10000, d;
    int i, index,idx;
    //locate maze contour
    for (i = 0; i < subMazeContour.size(); i++){
        d = fabs(pointPolygonTest(subMazeContour[i], p, true));
        if ( d < dist){
            dist = d;
            index = i;
        }
    }
    //locate pin
    dist = 10000;
    for (i = 0; i < pinSet[index].size(); i++){
        d =fabs(pointPolygonTest(Contour(1,pinSet[index][i]), p, true));
        if (d < dist){
            dist = d;
            idx = i;
        }
    }
    return nameSet[index] + idx;
}

#define DCON "Detect Connections"
int ScanMaze::checkPossibleNextC(Mat& img, list<PointAndStep>& q,
                                 int thisColor){
    //
    //5 possible step direction: left, left front, front, right front, right
    //only choose right angle direction in this case
    for (int sequence = 0; sequence < 5; sequence+=2){
        Point possibleStep = getNextStep(q.front().second, sequence);
        //Point next = findColorBreak(img, q.front().first, possibleStep);
        Point next = q.front().first + possibleStep;
        char c = getColor(img, next);
        if (c == 'W')
            continue;
        if (c == thisColor){
            //adjust to middle after change of direction
            if (sequence !=2 ){
                Point start = next + q.front().second, end = next - q.front().second;
                //next = findLineMiddle(binImg, start, end);
                next = findLineMiddle(binImg, next, q.front().second);
            }
            q.push_back(PointAndStep(next, possibleStep));
            continue;
        }
        //cross point, track the original step
        if (c != 'D'){
            if (sequence != 2)
                continue;
            Point bStep = q.front().second * 0.5;
            next = findColorBreak(img, next, bStep);
            if (getColor(img, next) == thisColor)
                q.push_back(PointAndStep(next, possibleStep));
            continue;
        }
        return 0;
    }
    return -1;
}


#define DIST(p1,p2) (abs((p1).x - (p2).x) + abs((p1).y - (p2).y))
int ScanMaze::checkPossibleNextG(Mat& img, list<PointAndStep>& q){
    Point end = q.front().first, step = q.front().second;
    end.x = step.x?(step.x<0?0:img.cols):end.x;
    end.y = step.y?(step.y<0?0:img.rows):end.y;
    Point p1, p2, p3, p4;
    LineIterator it(img, q.front().first, end, 4);
    if (!findGrayBreak(img, it, end))
        return -1;
    p1 = it.pos() - step;
    if (onBorder(p1, 2*wireWidth)){
        return 0;
    }
    if (!findGrayBreak(img, it, end))
        return -1;
    p2 = it.pos() - step;
    
    //normal corner
    if (DIST(p1,p2) > wireWidth){
        for (int sequence = 0; sequence < 5; sequence+=4){//test left, right
            Point possibleStep = getNextStep(q.front().second, sequence);
            Point next = p1 + possibleStep;
            char c = getGrayLevel(img, next);
            if (c == 0)
                continue;
            q.push_back(PointAndStep(next, possibleStep));
        }
        return 1;
    }
    if (!findGrayBreak(img, it, end))
        return -1;
    p3 = it.pos() - step;
    //cross point
    if (DIST(p3, p2) > wireWidth){
        for (int sequence = 0; sequence < 5;sequence+=2){//test left,front,right
            Point possibleStep = getNextStep(q.front().second, sequence);
            //(p2 + p1) * 0.5 = center of cross point
            //DIST(p1, p2) = diameter of corss point circle
            //change direction and jump out of cross point
            Point next = (p2 + p1)* 0.5 + DIST(p1,p2) * possibleStep;
            char c = getGrayLevel(img, next);
            if (c == 0)
                continue;
            q.push_back(PointAndStep(next, possibleStep));
        }
        return 1;
    }
    if (!findGrayBreak(img, it, end))
        return -1;
    p4 = it.pos();
    //non-cross point
    if (DIST(p1,p4)< wireWidth *3){
        q.push_back(PointAndStep(p4, step));
        return 1;
    }

    //quaint point, try left right of p1(befor 1st color break), like corner
    for (int sequence = 0; sequence < 5; sequence+=4){//test left, right
        Point possibleStep = getNextStep(q.front().second, sequence);
        Point next = p1 + possibleStep;
        char c = getGrayLevel(img, next);
        if (c == 0)
            continue;
        q.push_back(PointAndStep(next, possibleStep));
    }
    return -1;
}

int ScanMaze:: trackWire(Mat& img, Point& src, set<string>& dsts, Point& step){
    Mat tmp = image.clone();
    list<PointAndStep > q;
    char thisColor = type==TYPE_COLOR?getColor(img, src):getGrayLevel(img, src);
    //color image and pin is unconnected
    if (type==TYPE_COLOR && thisColor == 'W')
        return -1;
    vector<Point> mark;//can not use set :( 
    for (q.push_back(PointAndStep(src, step)); !q.empty();
         mark.push_back(q.front().first), q.pop_front()){
        if (debug)
            drawPoint(tmp, q.front().first, 'G');

        vector<Point>::iterator pit = find (mark.begin(), mark.end(), q.front().first);
        if (pit != mark.end())
            continue;

        if (type == TYPE_COLOR){
            if (checkPossibleNextC(img, q, thisColor) == 0){
                Point p= findColorBreak(img, q.front().first,
                                        q.front().second);
                if (debug)
                    drawPoint(tmp, p, 'G');
                dsts.insert(locatePin(p));
            }
        }else{//gray image
            if (checkPossibleNextG(img, q) ==0){
                Point p = findGrayBreak(img, q.front().first,
                                        q.front().second) - q.front().second;
                if (debug)
                    drawPoint(tmp, p, 'G');
                dsts.insert(locatePin(p));
            }
        }
    }

    if (debug){
        imshow(DCON, tmp);
        waitKey(0);
    }
    
    return 0;
}

int ScanMaze::detectConnections(){
    Mat img = type==TYPE_GRAY?binImg:image;

    set<string> mark;
    //each maze
    for (int i = 0; i < pinSet.size(); i++){
        //each pin point
        vector<Point>& maze = pinSet[i];
        for (int j = 0; j < maze.size(); j++){
            //calculate direction and step
            Point step = getDirection(maze, j) * (i?-1:1);
            if (type == TYPE_COLOR) step *= wireWidth;
            Point src = type==TYPE_GRAY?maze[j]:findColorBreak(img, maze[j], step);
            set<string> dsts;

            if (mark.count(nameSet[i] + j))
                continue;
                
            trackWire(img, src, dsts, step);

            if (!dsts.size())
                continue;
            
            //restore
            set<string> *con = NULL;
            //
            string pole = dsts.count("Anode")?"Anode":dsts.count("Cathode")?"Cathode":"";
            bool allocateNew = false;
            if ( !pole.empty()){
                for (vector<set<string> >::iterator k = connections.begin(); k != connections.end(); k++){
                    if ((*k).count(pole))
                        con = &(*k);
                }
            }
            if (!con){
                con = new set<string>;
                allocateNew = true;
            }

            //
            for (set<string>::iterator it = dsts.begin(); it != dsts.end(); it++){
                con->insert(*it);
                mark.insert(*it);
            }
            con->insert(nameSet[i] + j);
            mark.insert(nameSet[i] + j);
            //if no dsts, but src may in dsts when track gray image
            if (con->size() <2)
                continue;
            if (allocateNew){
                connections.push_back((*con));
                delete con;
            }
        }
    }
    return 0;
}

int ScanMaze::displayConnections(){
    save();
    return 0;
}

