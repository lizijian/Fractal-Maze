#ifndef OPENMAZE_H
#define OPENMAZE_H

#include <QDialog>
#include <QString>
#include <QDir>

namespace Ui {
    class OpenMaze;
}

class OpenMaze : public QDialog
{
    Q_OBJECT

public:
    explicit OpenMaze(QWidget *parent = 0);
    ~OpenMaze();
    QString selectedMaze;
    int exec();

private slots:
    void on_btnOK_clicked();
    //void onImageClicked();

private:
    Ui::OpenMaze *ui;
};

#endif // OPENMAZE_H
