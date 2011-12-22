#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QtCore/QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gbk"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gbk"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
