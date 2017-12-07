#include "mainwindow.h"
#include"mythread.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mythread my;
    my.start();
    //MainWindow w;
   // w.show();

    return a.exec();
}
