#include "maze.hpp"

Maze::Maze(string name):chip(0, ("mazes/" + name + "/" + name + ".ana").c_str())
{
    //load image
    img.load(("mazes/" + name + "/" + name).c_str());
    markedImage = img.copy();

    //load pin points location file
    QFile file(("mazes/" + name + "/" + name + ".loc").c_str());
    if (!file.open(QIODevice::ReadOnly)){
        cout <<"can not open loc file."<<endl;
        return;
    }
    QTextStream in(&file);
    while(!in.atEnd()){
        QString tmpName;
        PINLOC tmpLoc;
        char rc;//redundant char
        in >>tmpName;
        if (tmpName.size() == 0)
            break;
        in >>rc;//skip ' '
        in >>rc;//skip '['
        in >>tmpLoc.rx();
        in >>rc;//skip ','
        in >>rc;//skip ' '
        in >>tmpLoc.ry();
        in >>rc;//skip ']'
        names.push_back(tmpName.toStdString());
        locs.push_back(tmpLoc);
    }

    // //add pins which connect with cathode to queue
    Q *thisq = new Q(this, "Cathode", NULL);
    q.push_back(thisq);

    updateStack();
}

void Maze::displayLoc(){
    for (size_t i = 0; i < names.size(); i++)
        cout <<names[i]<<" :"<<locs[i].x()<<","<<locs[i].y()<<endl;
}

PINNAME Maze::nearPin(PINLOC loc){
    int mind = 1000, index;
    for (size_t i = 0; i < locs.size(); i++){
        int d = (loc - locs[i]).manhattanLength();
        if (d < mind){
            mind = d;
            index = i;
        }
    }
    if (mind < 5)
        return names[index];
    return PINNAME();
}

bool Maze::isConnectedPin(PINNAME& pin){
    if (this->q.empty())
        return false;
    if (!conn.count(q.back()->pin))
        return false;
    //cout <<"set ="<<conn[q.back()->pin]<<endl;
    //cout <<"cout ="<<conn[q.back()->pin].count(pin)<<endl;
    return conn[q.back()->pin].count(pin);
}

int Maze::insert(PINNAME& pin){
    Q *thisq = q.back();
    int res = chip::insert(thisq, pin);

    updateStack();

    switch(res){
    case InsertOK:
        return InsertOK;
    case NoConnections:
        undo(false);
        return NoConnections;
    case ReachAnode:
        return ReachAnode;
    }



    //Q *thisq = q.back();
    //Q *node = new Q(thisq->loc, pin, thisq);
    //insertQ(node);
//
    //thisq = q.back();
    //if (pin[0] != 'P'){//into subChip
    //    //calculate sub chip number
    //    int index = thisq->pin[0] - 'A';
    //    //cout <<"thisq="<<*thisq<<endl;
    //    //if sub chip has not been visited, construct it
    //    if (!thisq->loc->child[index])
    //        thisq->loc->child[index] = new chip(thisq->loc->level + 1);
//
    //    //generate new queue node, insert to queue
    //    node = new Q(thisq->loc->child[index], thisq->pin, thisq);//XXX
    //    node->pin[0] = 'P';
    //    insertQ(node);
    //}else{//pin out
    //    Q *n;
    //    for (n = thisq->pre; n ; n = n->pre)//find parent chip
    //        if ( n->loc->level == thisq->loc->level -1)
    //            break;
    //    if (!n){//no parent node was finded
    //        node = q.back();
    //        q.pop_back();
    //        delete node;
    //        return NoConnections;
    //    }
//
    //    node = new Q(n->loc, thisq->pin, thisq);
    //    node->pin[0] = n->pin[0];
    //    insertQ(node);
    //}
//
    ////if no connections
    //if ( !conn.count(q.back()->pin) ){
    //    undo(false);
    //    return NoConnections;
    //}
//
    //updateStack();
//
    ////find anode?
    //PINSET& pset = conn[q.back()->pin];
    //if (pset.count(string("Anode")))
    //    return ReachAnode;
//
    //return InsertOK;
}

void Maze::updateMark(){
    Q *thisq = q.back();
    markedImage = img.copy();
    QPainter tmp(&markedImage);

    //potential pin
    tmp.setPen(QPen(Qt::green, 4, Qt::DashLine, Qt::RoundCap));
    PINSET &toSet = getConn()[thisq->pin];
    for (size_t i = 0; i < names.size(); i++){
        if (!toSet.count(names[i]))
            continue;
        tmp.drawEllipse(locs[i], 5, 5);
    }

    //visited pin
    tmp.setPen(QPen(Qt::red, 14, Qt::DashLine, Qt::RoundCap));
    PINSET &flagSet = thisq->loc->getFlag();
    for (size_t i = 0; i < names.size(); i++){
        if (!flagSet.count(names[i]))
            continue;
        tmp.drawPoint(locs[i]);
    }

    //this
    tmp.setPen(QPen(Qt::yellow, 14, Qt::DashLine, Qt::RoundCap));
    for (size_t i = 0; i < names.size(); i++){
        if (names[i] == thisq->pin)
            tmp.drawPoint(locs[i]);
    }

}

int Maze::undo(bool cleanFlag){
    Q* node = q.back();
    if (node->pin == "Cathode")
        return -1;
    int level = node->loc->getLevel();
    q.pop_back();
    if (cleanFlag)
        node->loc->getFlag().erase(node->pin);
    delete node;

    //last action = step into/out, remove relative nodes
    node = q.back();
    if (node->loc->getLevel() != level){
        q.pop_back();
        if (cleanFlag)
            node->loc->getFlag().erase(node->pin);
        delete node;
    }
    updateStack();
    return 0;
}

void Maze::updateStack(){
    QString& tmp = mazeStack;
    tmp.clear();

    int level = q.back()->loc->getLevel();
    for (Q* node = q.back(); node->pre; node = node->pre){
        if (node->loc->getLevel() == level){
            Q* n;
            for (n = node->pre; n ; n = n->pre)//find parent chip
                if ( n->loc->getLevel() == node->loc->getLevel() -1)
                    break;
            if (!n)
                continue;
            //calculate index
            int i;
            for (i = 0; i < childN; i++)
                if (n->loc->getChild()[i] == node->loc)
                    break;
            tmp.push_front('A' + i);
            level--;
        }
    }
    tmp.push_front("Stack : M");
    tmp.push_back("  ");
}
