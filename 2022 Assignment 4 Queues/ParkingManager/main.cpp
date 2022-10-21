#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "Queue.h"

const bool DEBUG = 0;

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

int main(int argc, char *argv[])
{
    if (DEBUG) {
        debugMain();
        return 0;
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
