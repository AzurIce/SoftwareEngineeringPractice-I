#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

//#include "stack.h"
//#include <vector>

void debug_main() {
//    std::vector vec1 = std::vector<int>();
//    std::vector vec2 = std::vector<int>();
//    vec1.push_back(1);
//    vec2.push_back(2);

//    vec1 = vec2;
//    for (auto i:vec1) {
//        std::cout << i << std::endl;
//    }
//    std::cout << std::endl;
//    for (auto i:vec2) {
//        std::cout << i << std::endl;
//    }
//    std::cout << std::endl;
//    printf("%x\n", &vec1);
//    printf("%x\n", &vec2);

//    return;

//    Stack<int> testStack1 = Stack<int>("test1");
//    Stack testStack2 = Stack<int>("test2");
//    Stack testStack3 = Stack<int>("test3");

//    testStack1 = testStack2;
//    printf("%x\n", &testStack1);
//    printf("%x\n", &testStack2);
//    std::cout << testStack1._stack << std::endl;
//    std::cout << testStack2._stack << std::endl;
//    std::cout << testStack1.name.toStdString() << std::endl;
//    std::cout << testStack2.name.toStdString() << std::endl;
    return ;
    /*
    std::cout << "wtf1???" << std::endl;

    std::cout << testStack1._stack << std::endl;
    std::cout << testStack2._stack << std::endl;
    std::cout << testStack3._stack << std::endl;
    std::cout << testStack1.name.toStdString() << std::endl;
    std::cout << testStack2.name.toStdString() << std::endl;
    std::cout << testStack3.name.toStdString() << std::endl;

//    return;

    testStack1 = Stack<int>("test11");
    testStack2 = Stack<int>("test22");
    testStack3 = Stack<int>("test33");

    std::cout << "wtf2???" << std::endl;

    std::cout << testStack1._stack << std::endl;
    std::cout << testStack2._stack << std::endl;
    std::cout << testStack3._stack << std::endl;
    std::cout << testStack1.name.toStdString() << std::endl;
    std::cout << testStack2.name.toStdString() << std::endl;
    std::cout << testStack3.name.toStdString() << std::endl;

//    testStack1 = Stack<int>("test111");
//    testStack1 = Stack<int>("test222");
//    testStack1 = Stack<int>("test333");

//    std::cout << "wtf3???" << std::endl;

//    std::cout << testStack1._stack << std::endl;
//    std::cout << testStack2._stack << std::endl;
//    std::cout << testStack3._stack << std::endl;
//    std::cout << testStack1.name.toStdString() << std::endl;
//    std::cout << testStack2.name.toStdString() << std::endl;
//    std::cout << testStack3.name.toStdString() << std::endl;
    */
}

int main(int argc, char *argv[])
{
    bool debug = 0;
    if (debug) {
        debug_main();
        return 0;
    }
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Calculator_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
