#include "huffman_tree.h"

#include <QDebug>

HuffmanTreeNode::HuffmanTreeNode(char x, unsigned long long w): x(x), w(w), lchild(nullptr), rchild(nullptr) {

}

HuffmanTree::HuffmanTree(std::map<char, unsigned long long> frequencyTable) {
//    qDebug() << "Building HuffmanTree...";
    std::vector<HuffmanTreeNode*> nodes;
    for (auto [byte, frequency]: frequencyTable) {
        nodes.push_back(new HuffmanTreeNode(byte, frequency));
    }

    unsigned long long n = nodes.size();
    for (int i = 1; i < n; i++) {
//        qDebug() << i << nodes.size();
//        for (auto j = nodes.begin(); j != nodes.end(); j++) {
//            qDebug() << (*j)->x << (*j)->w;
//        }
        auto minNode = *nodes.begin(), minNode2 = *(nodes.begin() + 1);

        if(nodes.size() > 2) for (auto j = nodes.begin() + 2; j != nodes.end(); j++) {
//            qDebug() << (*j)->x;
            if ((*j)->w < minNode->w) {
                minNode2 = minNode;
                minNode = *j;
            } else if ((*j)->w < minNode2->w) {
                minNode2 = *j;
            }
        }

//        qDebug() << "minIt:  " << minNode->x << minNode->w;
//        qDebug() << "minIt2: " << minNode2->x << minNode2->w;
        auto newNode = new HuffmanTreeNode(0, minNode->w + minNode2->w);
        for (auto j = nodes.begin(); j != nodes.end();) {
            if (*j == minNode || *j == minNode2) {
                j = nodes.erase(j);
            } else {
                j++;
            }
        }
        newNode->lchild = minNode;
        newNode->rchild = minNode2;
        nodes.push_back(newNode);
        root = newNode;
    }

//    qDebug() << "Finished.";
}

std::ostream &operator<<(std::ostream &os, const HuffmanTreeNode &o) {
    os << o.x << "(" << o.w << ")" << std::endl;
    if (o.lchild != nullptr) os << o.x << "(" << o.w << ") - l:" << *o.lchild;
    if (o.rchild != nullptr) os << o.x << "(" << o.w << ") - r:" << *o.rchild;
    return os;
}

std::ostream &operator<<(std::ostream &os, const HuffmanTree &t) {
    os << *t.root;
    return os;
}
