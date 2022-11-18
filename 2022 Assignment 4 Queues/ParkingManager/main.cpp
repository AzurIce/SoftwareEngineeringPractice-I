#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

//#define DEBUG

#ifdef DEBUG
#include "queue.h"

void debugMain() {
    Queue<int> testQ;
    for (int i = 0; i <= 20; i++) {
        testQ.push(i);
        qDebug() << "size: " << testQ.size() << " | " << testQ.toString();
        qDebug() << testQ._front << " " << testQ._rear;
    }

    while (!testQ.empty()) {
        qDebug() << "size: " << testQ.size() << " | " << testQ.toString();
        qDebug() << testQ._front << " " << testQ._rear;
        testQ.pop();
    }


    for (int i = 0; i <= 20; i++) {
        testQ.push(i);
        qDebug() << "size: " << testQ.size() << " | " << testQ.toString();
        qDebug() << testQ._front << " " << testQ._rear;
    }

    while (!testQ.empty()) {
        qDebug() << "size: " << testQ.size() << " | " << testQ.toString();
        qDebug() << testQ._front << " " << testQ._rear;
        testQ.pop();
    }
}
#endif

int main(int argc, char *argv[])
{
#ifdef DEBUG
    debugMain();
    return 0;
#else
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#endif
}
