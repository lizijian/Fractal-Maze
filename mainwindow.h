#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sstream>
#include <QtGui>
#include <QLabel>
#include "maze.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onImageLeftClicked(int x, int y);
    void onMouseMoved(int x, int y);
    void undoPressed();

private slots:
    void on_actionOpen_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    Maze* maze;
    QLabel *info;
    QLabel *stack;
};

#endif // MAINWINDOW_H
