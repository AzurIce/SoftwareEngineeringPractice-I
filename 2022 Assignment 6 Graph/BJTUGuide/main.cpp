#include "mainwindow.h"

#include <QApplication>
//#include <QDebug>
//#include <iostream>

int main(int argc, char *argv[])
{
//    qDebug() << "?";
//    std::cout << "??" << std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
