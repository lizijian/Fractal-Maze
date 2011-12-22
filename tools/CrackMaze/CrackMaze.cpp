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
#include "CrackMaze.hpp"

//#define DEBUG

using namespace std;

int chip::childN;
CONN chip::conn;
PIN chip::dest;
list<Q*> chip::q;
list<Q*>::iterator chip::qfront;

ostream& operator << (ostream &os, const PINSET &s){
    os << "[ ";
    for (set<string>::const_iterator iter = s.begin(); iter !=s.end(); iter++)
        os << *iter <<" ";
    os << " ]"<<endl;
    return os;
}

ostream& operator << (ostream &os, Q &q){
#ifdef DEBUG
    os <<"("<<q.pre <<","<<q.pin<<","<<q.loc<<","<<q.loc->level<<")"<<" ";
#else
    os <<"("<<q.pin<<","<<q.loc->level<<")"<<" ";
#endif
    return os;
}

ostream& operator << (ostream &os, list<Q*> &v){
    os << "[ ";
    for (list<Q*>::iterator iter = v.begin(); iter !=v.end(); iter++)
        os <<*(*iter);
    os << " ]"<<endl;
    return os;
}

chip::chip(){}

void chip::buildSet(string s){
    //cout <<s<<endl;
    istringstream ss (s, istringstream::in);
    string str;
    typedef CONN::value_type vt;
    PINSET tmp;
    while (getline(ss,str,' '))
        tmp.insert(str);
    
    //remove repetitive element
    for (PINSET::iterator it = tmp.begin(); it != tmp.end(); it++ ){
        chip::conn[*it] = tmp;
        chip::conn[*it].erase(*it);

        //calculate sub chip number
        char pname = (*it)[0];
        if (pname != 'P' && pname - 'A' + 1 > childN)
            childN = pname - 'A' + 1;
    }

}

chip::chip(int level,const char* srcFile):level(level){
    if (level == 0){
        ifstream infile(srcFile);
        if (!infile.is_open()){
            cout <<"Can't open input file "<<srcFile<<endl;
            exit (-1);
        }
        conn.clear();
        string s;
        while (getline(infile,s))
            buildSet(s);
    }
    
    child = new chip*[chip::childN];
    for (int i = 0; i < chip::childN ; i++)
        child[i] = NULL;

    dest = "Anode";
}

void chip::displayConn(){
    for (CONN::iterator iter = chip::conn.begin();
         iter != chip::conn.end(); iter++){
        cout <<endl<<(*iter).first<<" => "<<((*iter).second);
    }
}

void chip::dumpQ(Q*node){
    vector<Q*> dump;
    for (Q* i = node ; i ;i = i->pre)
        dump.push_back(i);
    cout <<endl<<"Trace: [";
    for (vector<Q*>::reverse_iterator it = dump.rbegin(); it != dump.rend(); it++)
        cout <<**it<<" ";
    cout << "]"<<endl;
}

int chip::insert(Q* thisq, const PIN& pin){
    Q* node;
    Q *node1 = new Q(thisq->loc, pin, thisq);
    insertQ(node1);

    if (pin[0] != 'P'){//into subChip
        //calculate sub chip number
        int index = pin[0] - 'A';
        //if sub chip has not been visited, construct it
        if (!thisq->loc->child[index])
            thisq->loc->child[index] = new chip(thisq->loc->level + 1);

        //generate new queue node, insert to queue
        node = new Q(thisq->loc->child[index], pin, node1);//XXX
        node->pin[0] = 'P';
        insertQ(node);
    }else{//pin out
        Q *n;
        for (n = thisq->pre; n ; n = n->pre)//find parent chip
            if ( n->loc->level == thisq->loc->level -1)
                break;
        if (!n){//no parent node was finded
            return NoConnections;
        }

        node = new Q(n->loc, pin, node1);
        node->pin[0] = n->pin[0];
        insertQ(node);
    }

    //if no connections
    if ( !conn.count(q.back()->pin) ){
        //undo(false);
        return NoConnections;
    }

    // //find anode?
    PINSET& pset = conn[q.back()->pin];
    if (pset.count(string("Anode")))
        return ReachAnode;

    return InsertOK;
}

void chip::trace(){
    while(!q.empty()){
        //Q* thisq = q.front();
        Q* thisq = *qfront;
        Q* preq = thisq->pre;
        if (preq && thisq->loc->level == preq->loc->level){
            //q.pop_front();
            qfront++;
            continue;
        }
        PINSET& toSet = conn[thisq->pin];
        int res;
        for (PINSET::iterator to = toSet.begin(); to != toSet.end(); to++){

            res = insert(thisq, *to);

            if (res == ReachAnode && q.back()->loc->level == 0){
                dumpQ(q.back());
                exit(0);
            }
        }
        //q.pop_front();
        qfront++;
    }
}

void chip::insertQ(QP &node){
    //if this pin has been visited 
    if (node->loc->flag.count(node->pin)){
        return;
    }

    //mark this pin visited
    node->loc->flag.insert(node->pin);
    //add new node into queue
    chip::q.push_back(node);
}

void chip::crack(){
    q.clear();
    Q *thisq = new Q(this, "Cathode", NULL);
    q.push_back(thisq);
    qfront = q.begin();
    chip::trace();
}

chip::~chip(){
    if (!level){
        for (list<Q*>::iterator it = q.begin(); it != q.end(); it++)
            delete *it;
        q.clear();
    }
    for (int i = 0; i < chip::childN ; i++)
        if (child[i])
            delete child[i];
    delete [] child;
}
