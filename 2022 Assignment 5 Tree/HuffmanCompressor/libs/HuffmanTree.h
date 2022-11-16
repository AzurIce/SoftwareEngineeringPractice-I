//
// Created by AzurIce on 2022/11/11.
//

#ifndef HUFFMANCOMPRESSOR_QT_HUFFMANTREE_H
#define HUFFMANCOMPRESSOR_QT_HUFFMANTREE_H

#include <QObject>
#include <QMap>
#include <ostream>
#include <QProgressDialog>

class HuffmanTreeNode {
public:
    HuffmanTreeNode(): x(0), w(0), lchild(nullptr), rchild(nullptr) {};
    HuffmanTreeNode(char x, unsigned int w);
    ~HuffmanTreeNode();

    std::vector<bool> toBits();
    static HuffmanTreeNode *fromBits(const std::vector<bool> &bits);
    static HuffmanTreeNode *fromBits(const std::vector<bool> &bits, int &index);
    friend std::ostream &operator<<(std::ostream &os, const HuffmanTreeNode &o);
    char x;
    unsigned long long w;
    HuffmanTreeNode *lchild, *rchild;
private:
//    friend QDataStream &operator>>(QDataStream &stream, HuffmanTreeNode &treeNode);
//    friend QDataStream &operator<<(QDataStream &stream, const HuffmanTreeNode &treeNode);
};

class HuffmanTree {
public:
    ////// Constructors and Destructors //////
    HuffmanTree(): root(nullptr) {};
    ~HuffmanTree();

    void init(const QMap<char, unsigned int> &byteHist);

    ////// Encoding and Decoding //////
    void getEncodingTable(HuffmanTreeNode * node, QMap<char, std::vector<bool>> &encodingTable, std::vector<bool> &code);

    void getDecodingTable(HuffmanTreeNode * node, QMap<std::vector<bool>, char> &decodingTable, std::vector<bool> &code);

    QByteArray encode(const QByteArray& bytes);

    QByteArray decode(const QByteArray& bytes, int size);

    ////// Printing //////
    friend std::ostream &operator<<(std::ostream &os, const HuffmanTree &t);

    ////// Serializing & Deserializing //////
    friend QDataStream &operator>>(QDataStream &stream, HuffmanTree &tree);
    friend QDataStream &operator<<(QDataStream &stream, const HuffmanTree &tree);

    int current{};
    int total{};
private:
    QMap<char, unsigned int> m_byteHist;
    HuffmanTreeNode *root;
};

#endif //HUFFMANCOMPRESSOR_QT_HUFFMANTREE_H
