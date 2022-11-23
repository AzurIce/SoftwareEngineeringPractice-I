#include "ui/mainwindow.h"

#include <QApplication>
#include <QmlTypeAndRevisionsRegistration>
#include "models/InterestPoint.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qmlRegisterType<InterestPoint>("MyClass.module", 1, 0, "MyQml");

    MainWindow w;
    w.show();
    return a.exec();
}
