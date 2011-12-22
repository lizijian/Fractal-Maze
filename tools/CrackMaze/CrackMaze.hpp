#ifndef __CRACK_MAZE__
#define __CRACK_MAZE__
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>

using namespace std;

class chip;

/*eg.*/
//---13-14-15-16-|
//11             12
//|              |
//9  A        B  10
//|              |
//7              8
//|  Cathode     |
//5  Anode    C  6
//|              |
//---1--2--3--4---

typedef string PIN;
typedef set<PIN> PINSET;
typedef map<PIN, PINSET> CONN;

//queue node
class Q{
public:
    Q(){};
    Q(chip* loc, PIN pin, Q *pre):loc(loc),pin(pin),pre(pre){};
    chip *loc;//pin location, point to chip/sub chip
    Q *pre;//previous node
    PIN pin;//pin name
};

class chip {
public:
    chip();
    chip( int level = 0, const char* srcFile = NULL);
    //program will quit immediately after solving, so we have
    //not to implement destructor to free memory
    ~chip();
    void displayConn();
    void crack();
    CONN& getConn(){return conn;}
    PINSET& getFlag(){return flag;}
    int& getLevel(){return level;}
    chip**& getChild(){return child;}
    enum {
        NoConnections=-1,
        InsertOK,
        ReachAnode
    };
protected:
    //pin number, sub chip number
    static int childN;
    //target pin name, default Anode
    static PIN dest;

    ////auxiliary fucntions
    //
    static void trace();
    //build up connections set
    void buildSet(string s);
    //dump trace queue contents
    static void dumpQ(Q*node);
    //function:insert queue point
    typedef Q* QP;
    static void insertQ(QP &node);
    static int insert(Q* thisq, const PIN& pin);
    friend ostream& operator << (ostream &os, vector<Q*> &v);
    friend ostream& operator << (ostream &os, Q &q);

    ////maze structure
    //maze level, main=0, sub maze = 1,2,3..
    int level;
    //sub mazes , dynamically allocate
    chip **child;//*child[]
    //connections set
    static CONN conn;
    //cracking runtime queue
    static list<Q*> q;
    //visited flag
    PINSET flag;
    //front of queue
    static list<Q*>::iterator qfront;
};
ostream& operator << (ostream &os, const PINSET &s);
ostream& operator << (ostream &os, Q &q);
ostream& operator << (ostream &os, list<Q*> &v);

#endif
