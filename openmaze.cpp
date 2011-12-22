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
