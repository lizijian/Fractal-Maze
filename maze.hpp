#ifndef MAZE_HPP
#define MAZE_HPP
#include <string>
#include "tools/CrackMaze/CrackMaze.hpp"
#include <QPixmap>
#include <QFile>
#include <QDir>
#include <QPoint>
#include <QTextStream>
#include <QPainter>

#define PINNAME string
#define PINLOC QPoint

class Maze : public chip
{
public:
    Maze(string name);
    const QPixmap& getImage(){return img;}
    const QPixmap& getMarkedImage(){return markedImage;}
    void displayLoc();
    PINNAME nearPin(PINLOC loc);
    bool isConnectedPin(PINNAME& pin);
    int insert(PINNAME& pin);
    int undo(bool clearFlag = true);
    void updateMark();
    QString& getMazeStack(){return mazeStack;}
    //enum {
    //    NoConnections=-1,
    //    InsertOK,
    //    ReachAnode
    //};
private:
    void updateStack();
    QPixmap img;
    QPixmap markedImage;
    vector<PINNAME> names;
    vector<PINLOC> locs;
    QString mazeStack;
};

#endif // MAZE_HPP
