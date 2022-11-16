#include "ui/mainwindow.h"

#include <QApplication>
#include <iostream>

//#define DEBUG
#ifdef DEBUG
#include <QDebug>
#include "models/FileTreeItem.h"
#include <iostream>
#include "utils/Utils.h"
#include "libs/HuffmanCompress.h"
#include <vector>
#endif

int main(int argc, char *argv[]) {
#ifdef DEBUG
//    bool arr[9];
//    std::cout << sizeof(arr) << std::endl;
    std::vector<bool> vec;
//        std::map<char, unsigned long long> m{{'A', 10}, {'B', 15}, {'C', 20}};
//        HuffmanTree t = HuffmanTree(m);
//        std::cout << t;

//    std::cout << "------TEST BINARY STRING CONVERSION------" << std::endl;
//    QByteArray arr = Utils::binaryStr2Bytes("0110101100");
//    for (char byte: arr) {
//        std::cout << '[' << (int)byte << ']';
//    }
//    std::cout << std::endl;
//    std::cout << Utils::bytes2BinaryStr(arr).toStdString() << std::endl;

/*

    std::cout << "------TEST FILETREEITEM------" << std::endl;

//    FileTreeItem origin = FileTreeItem(R"(F:\Syncthing\Notes\Coding\C++\qt)");
    FileTreeItem origin = FileTreeItem(R"(F:\Syncthing\School\cxd\2022 Assignment 5 Tree\testin)");
//    FileTreeItem cf = FileTreeItem("D:\\_Files\\Syncthing\\School\\离散数学\\Program Work 1 (2022)");
    std::cout << origin;

//    std::cout << "------TEST SERIALIZING------" << std::endl;
//
    QByteArray originalBytes;
    origin.toBytes(&originalBytes);
    FileTreeItem item = FileTreeItem::fromBytes(&originalBytes);
    Utils::saveBytes(originalBytes, "F:\\Syncthing\\School\\cxd\\2022 Assignment 5 Tree\\test_original");
//    std::cout << item;
//
//    std::cout << "------TEST FILE------" << std::endl;
//
//    Utils::saveBytes(arr, R"(F:\Syncthing\School\cxd\2022 Assignment 5 Tree\test)");
//    QByteArray fileContent = Utils::readBytes(R"(F:\Syncthing\School\cxd\2022 Assignment 5 Tree\test)");
//    FileTreeItem fromFile = FileTreeItem::fromBytes(&fileContent);
//    std::cout << item;

    HuffmanCompress compress = HuffmanCompress(originalBytes);
    QByteArray &&compressedBytes = compress.toCompressedBytes();
    Utils::saveBytes(compressedBytes, "F:\\Syncthing\\School\\cxd\\2022 Assignment 5 Tree\\test_zipped");
    qDebug() << compressedBytes.size();

//    QByteArray originReadCompressBytes = Utils::readBytes("F:\\Syncthing\\School\\cxd\\2022 Assignment 5 Tree\\test_compress_original");
//    HuffmanCompress readCompress = HuffmanCompress::fromCompressedBytes(&originReadCompressBytes);
//    qDebug() << originReadCompressBytes.size();

*/
    return 0;
#else
//    std::cout << "Hello!" << std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
#endif
}
