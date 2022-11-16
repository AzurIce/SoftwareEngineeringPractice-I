#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <QByteArray>
#include <ostream>
#include <vector>
#include <map>

class HuffmanTreeNode {
public:
    HuffmanTreeNode(char x, unsigned long long w);
    char x;
    unsigned long long w;
    HuffmanTreeNode *lchild, *rchild;
private:
    friend std::ostream &operator<<(std::ostream &os, const HuffmanTreeNode &o);
};

class HuffmanTree {
public:
    HuffmanTree(std::map<char, unsigned long long> frequencyTable);
    friend std::ostream &operator<<(std::ostream &os, const HuffmanTree& t);
private:
    HuffmanTreeNode *root;
};

#endif // HUFFMANTREE_H
