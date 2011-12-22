#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openmaze.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    maze = NULL;
    ////init status bar
    //m_pStatus = new QStatusBar();
    //setStatusBar(m_pStatus);
    stack = new QLabel;
    info = new QLabel;
    statusBar()->addWidget(stack);
    statusBar()->addWidget(info);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    OpenMaze om;
    if (om.exec() != OpenMaze::Accepted)
        return;

    if (maze)
        delete maze;
    maze = new Maze(om.selectedMaze.toStdString());
    //test
    //maze->crack();
    //

    //display image
    maze->updateMark();
    this->setFixedSize(maze->getMarkedImage().size() + QSize(20,70));
    ui->displayArea->setFixedSize(maze->getMarkedImage().size());
    ui->displayArea->setPixmap(maze->getMarkedImage());
    stack->setText(maze->getMazeStack());
    info->setText("Maze init ok!");

    //enable actions
    ui->actionUndo->setEnabled(true);

    disconnect(ui->displayArea, SIGNAL(leftClickImage(int, int)),
            this, SLOT(onImageLeftClicked(int, int)));
    disconnect(ui->displayArea, SIGNAL(mouseMove(int,int)),
            this, SLOT(onMouseMoved(int,int)));
    disconnect(ui->actionUndo, SIGNAL(triggered()),
            this, SLOT(undoPressed()));
    //connect to slot
    if (!connect(ui->displayArea, SIGNAL(leftClickImage(int, int)),
            this, SLOT(onImageLeftClicked(int, int))))
        info->setText("Left click connect fail.");
    if (!connect(ui->displayArea, SIGNAL(mouseMove(int,int)),
            this, SLOT(onMouseMoved(int,int))))
        info->setText("Mouse move connect fail.");
    if (!connect(ui->actionUndo, SIGNAL(triggered()),
            this, SLOT(undoPressed())))
        info->setText("Undo connect fail.");
}

void MainWindow::onImageLeftClicked(int x, int y){
    PINNAME pin = maze->nearPin(PINLOC(x, y));
    if (pin.empty())
        return;
    if(!maze->isConnectedPin(pin))
        return;

    int res = maze->insert(pin);
    switch (res){
    case -1:
        info->setText(QString("No connections"));
        break;
    case 0:
        info->setText(QString("Left Click: x:%1,y:%2 =>Pin:%3")
                               .arg(x).arg(y).arg(QString(pin.c_str())));
        break;
    case 1:
        disconnect(ui->displayArea, SIGNAL(mouseMove(int,int)),
                   this, SLOT(onMouseMoved(int,int)));
        info->setText(QString("You make it."));
        break;
    }
    maze->updateMark();
    ui->displayArea->setPixmap(maze->getMarkedImage());
    stack->setText(maze->getMazeStack());
}

void MainWindow::undoPressed(){
    if (!maze)
        return;
    if (maze->undo() == -1){
        info->setText(QString("Only cathode now."));
        return;
    }

    maze->updateMark();
    ui->displayArea->setPixmap(maze->getMarkedImage());
    info->setText(QString("Undo successful."));
    stack->setText(maze->getMazeStack());
}

void MainWindow::on_actionAbout_triggered()
{
   QMessageBox::about(this, tr("About Fractal Maze"),
            tr("This <b>Application</b> is a exercise of learning Opencv, "
               "it utilizes the result of opencv graphical analysis and maze "
               "image as input files and provides a interactive GUI to players."
               "<br>If you want to know how those .ana files are generated,"
               "please refer to: "
               "<b>tools/AnalyzeMaze</b>"
               "<br>Or you can't solve them, please refer to: "
               "<b>tools/CrackMaze</b>"
               "<br>If you have <b>good ideas</b>, please send Email to: "
               "<b>ijetlee@gmail.com</b><br>"
               ));
}


void MainWindow::onMouseMoved(int x, int y){
    PINNAME pin = maze->nearPin(PINLOC(x, y));
    info->setText(QString("[%1, :%2] =>Pin:%3")
                  .arg(x).arg(y).arg(QString(pin.c_str())));
}
