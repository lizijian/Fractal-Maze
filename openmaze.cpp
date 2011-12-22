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

#include "openmaze.h"
#include "ui_openmaze.h"
#include <QtGui>

OpenMaze::OpenMaze(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenMaze)
{
    ui->setupUi(this);

}

OpenMaze::~OpenMaze()
{
    delete ui;
}

int OpenMaze::exec(){
    QDir dir("mazes");
    if (!dir.exists())
        return OpenMaze::Rejected;
    dir.setFilter(QDir::Dirs);
    //dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();
    int i=0;
    do{
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName()=="." || fileInfo.fileName()==".."){
            i++;
            continue;
        }
        ui->listMazes->addItem(fileInfo.fileName());
        i++;
    }while(i < list.size());

    return QDialog::exec();
}

void OpenMaze::on_btnOK_clicked()
{
    if (ui->listMazes->currentItem())
        selectedMaze = ui->listMazes->currentItem()->text();
}
