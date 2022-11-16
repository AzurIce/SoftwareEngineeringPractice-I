//
// Created by AzurIce on 2022/11/11.
//

#include "HuffmanTree.h"
#include "utils/Utils.h"

#include <QDebug>
#include <iostream>
#include <vector>

HuffmanTreeNode::HuffmanTreeNode(char x, unsigned int w) : x(x), w(w), lchild(nullptr), rchild(nullptr) {}

HuffmanTreeNode::~HuffmanTreeNode() {
    delete lchild;
    delete rchild;
}

HuffmanTree::~HuffmanTree() {
    delete root;
}

void HuffmanTree::init(const QMap<char, unsigned int> &byteHist) {
    if (root != nullptr) {
        delete root;
        root = nullptr;
    }
    m_byteHist = byteHist;
    std::vector<HuffmanTreeNode *> nodes;
    for (auto it = byteHist.begin(); it != byteHist.end(); it++) {
        nodes.push_back(new HuffmanTreeNode(it.key(), it.value()));
    }

    unsigned long long n = nodes.size();
    for (int i = 1; i < n; i++) {
        auto minNode = *nodes.begin(), minNode2 = *(nodes.begin() + 1);
        if (minNode->w > minNode2->w) std::swap(minNode, minNode2);

        if (nodes.size() > 2)
            for (auto j = nodes.begin() + 2; j != nodes.end(); j++) {
                if ((*j)->w < minNode->w) {
                    minNode2 = minNode;
                    minNode = *j;
                } else if ((*j)->w < minNode2->w) {
                    minNode2 = *j;
                }
            }

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
}

void HuffmanTree::getEncodingTable(HuffmanTreeNode *node, QMap<char, std::vector<bool>> &encodingTable,
                                   std::vector<bool> &code) {
    if (node->lchild == nullptr && node->rchild == nullptr) {
        encodingTable[node->x] = code;
        return;
    }
    if (node->lchild != nullptr) {
        code.push_back(0);
        getEncodingTable(node->lchild, encodingTable, code);
        code.pop_back();
    }
    if (node->rchild != nullptr) {
        code.push_back(1);
        getEncodingTable(node->rchild, encodingTable, code);
        code.pop_back();
    }
}

void HuffmanTree::getDecodingTable(HuffmanTreeNode *node, QMap<std::vector<bool>, char> &decodingTable,
                                   std::vector<bool> &code) {
    if (node->lchild == nullptr && node->rchild == nullptr) {
        decodingTable[code] = node->x;
        return;
    }
    if (node->lchild != nullptr) {
        code.push_back(0);
        getDecodingTable(node->lchild, decodingTable, code);
        code.pop_back();
    }
    if (node->rchild != nullptr) {
        code.push_back(1);
        getDecodingTable(node->rchild, decodingTable, code);
        code.pop_back();
    }
}

QByteArray HuffmanTree::encode(const QByteArray &bytes) {
    std::vector<bool> code;
    QMap<char, std::vector<bool>> encodingTable;
    getEncodingTable(root, encodingTable, code);

    total = bytes.size();
    current = 0;
//    progress->setMaximum(total);

    std::vector<bool> bits;
    for (int i = 0; i < bytes.size(); i++) {
        char &&byte = bytes.at(i);
        bits.insert(bits.end(), encodingTable[byte].begin(), encodingTable[byte].end());
        current = i;
//        progress->setValue(current);
    }
    current = total;
//    progress->setValue(total);

    return Utils::bits2Bytes(bits);
}

QByteArray HuffmanTree::decode(const QByteArray &encodedBytes, int size) {
    std::vector<bool> encodedBits = Utils::bytes2Bits(encodedBytes);
    total = size;
    current = 0;
//    progress->setMaximum(total);
//    qDebug() << "decode total:" << total;

    QByteArray decodedBytes;
    auto cur = root;

    for (bool bit : encodedBits) {
//        qDebug("%d", bit);
        if (!bit && cur->lchild == nullptr || bit && cur->rchild == nullptr) {
            decodedBytes.push_back(cur->x);
            cur = root;
            current = decodedBytes.size();
//            progress->setValue(current);
//            qDebug() << "decoded:" << current;
            if (current == size) break;
        }
        if (!bit) cur = cur->lchild;
        else cur = cur->rchild;
    }
    current = total;
//    progress->setValue(total);
    return decodedBytes;
}

std::ostream &operator<<(std::ostream &os, const HuffmanTreeNode &o) {
    os << (int) o.x << "(" << o.w << ")" << std::endl;
    if (o.lchild != nullptr) os << o.x << "(" << o.w << ") - l:" << *o.lchild;
    if (o.rchild != nullptr) os << o.x << "(" << o.w << ") - r:" << *o.rchild;
    return os;
}

std::ostream &operator<<(std::ostream &os, const HuffmanTree &t) {
    os << *t.root;
    return os;
}

QDataStream &operator<<(QDataStream &stream, const HuffmanTree &tree) {
    auto bits = tree.root->toBits();
    stream << Utils::bits2Bytes(bits);
    return stream;
}

QDataStream &operator>>(QDataStream &stream, HuffmanTree &tree) {
    QByteArray bytes;
    stream >> bytes;
    tree.root = HuffmanTreeNode::fromBits(Utils::bytes2Bits(bytes));

    return stream;
}


std::vector<bool> HuffmanTreeNode::toBits() {
    std::vector<bool> bits;
    if (lchild == nullptr && rchild == nullptr) {
        bits.push_back(1);
        auto &&bitsX = Utils::byte2Bits(x);
        bits.insert(bits.end(), bitsX.begin(), bitsX.end());
        return bits;
    }
    bits.push_back(0);
    bits.push_back(lchild != nullptr);
    if (lchild != nullptr) {
        auto &&bitsL = lchild->toBits();
        bits.insert(bits.end(), bitsL.begin(), bitsL.end());
    }
    bits.push_back(rchild != nullptr);
    if (rchild != nullptr) {
        auto &&bitsR = rchild->toBits();
        bits.insert(bits.end(), bitsR.begin(), bitsR.end());
    }
    return bits;
}

HuffmanTreeNode *HuffmanTreeNode::fromBits(const std::vector<bool> &bits) {
    int index = 0;
    return fromBits(bits, index);
}

HuffmanTreeNode *HuffmanTreeNode::fromBits(const std::vector<bool> &bits, int &index) {
    auto node = new HuffmanTreeNode();
    if (bits[index++]) {
        int c = 0;
        for (int i = 0; i < 8 && index + i < bits.size(); i++, index++) {
            c = c << 1 | bits[index];
        }
        node->x = (char)c;
    } else {
        if (bits[index++]) {
            node->lchild = fromBits(bits, index);
        }
        if (bits[index++]) {
            node->rchild = fromBits(bits, index);
        }
    }
    return node;
}