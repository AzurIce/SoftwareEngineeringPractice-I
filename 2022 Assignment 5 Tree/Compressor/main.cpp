#include "mainwindow.h"

#include <QApplication>

//#define DEBUG
#ifdef DEBUG
#include "huffman_tree.h"
#include "compressed_file.h"
#include <iostream>
#endif

int main(int argc, char *argv[])
{
#ifdef DEBUG
//    std::map<char, unsigned long long> m{{'A', 10}, {'B', 15}, {'C', 20}};
//    HuffmanTree t = HuffmanTree(m);
//    std::cout << t;
//    CompressedFile cf = CompressedFile("D:\\_Files\\Syncthing\\School\\离散数学\\Program Work 1 (2022)");
    CompressedFile cf = CompressedFile("F:\\Syncthing\\Notes\\Coding\\C++\\qt");

#else

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#endif
}
