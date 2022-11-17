//
// Created by AzurIce on 2022/11/10.
//

#include "HuffmanCompress.h"
#include "utils/utils.h"
#include <iostream>
#include <QDebug>

////// Constructors and destructors //////
// Construct from original data bytes
HuffmanCompress::HuffmanCompress(const QByteArray &bytes, std::atomic<int> &current, std::atomic<int> &total) : current(
        current), total(total) {
    m_original_data_bytes = new QByteArray(bytes);
    m_size = bytes.size();

    state = ENCODING;
    m_huffmanTree.init(Utils::getBytesHist(bytes));
    state = DONE;
}

HuffmanCompress::~HuffmanCompress() {
    delete m_original_data_bytes;
}

////// Serializing and Deserializing //////
/*
 * Serialize and Deserialize will use compressed data bytes
 */

// Serialize
QByteArray HuffmanCompress::toBytes() {
    QByteArray bytes;
    QDataStream s(&bytes, QIODevice::ReadWrite); // 这里也可以跟 QFile关联

    s << m_huffmanTree
      << m_size
      << getCompressedBytes();
    return bytes;
}

// Deserialize
HuffmanCompress *HuffmanCompress::fromBytes(QByteArray *bytes, std::atomic<int> &current, std::atomic<int> &total) {
    auto *compress = new HuffmanCompress(current, total);

    compress->m_compressed_data_bytes = new QByteArray();

    QDataStream s(bytes, QIODevice::ReadOnly);
    s >> compress->m_huffmanTree
      >> compress->m_size
      >> *compress->m_compressed_data_bytes;

    return compress;
}

void HuffmanCompress::encode() {
    m_compressed_data_bytes = new QByteArray();
    state = COMPRESSING;
    auto encodingTable = m_huffmanTree.getEncodingTable();

    total = m_size;
    std::vector<bool> bits;
    for (int i = 0; i < m_original_data_bytes->size(); i++) {
        char &&byte = m_original_data_bytes->at(i);
        bits.insert(bits.end(), encodingTable[byte].begin(), encodingTable[byte].end());
        current = i + 1;
    }
    current = m_size;

    *m_compressed_data_bytes = Utils::bits2Bytes(bits);
    state = DONE;
}

void HuffmanCompress::decode() {
    m_original_data_bytes = new QByteArray();
    state = DECOMPRESSING;
    std::vector<bool> encodedBits = Utils::bytes2Bits(*m_compressed_data_bytes);
    total = m_size;

    auto cur = m_huffmanTree.root;
    for (bool bit: encodedBits) {
        if (cur->lchild == nullptr) { // 叶子节点
            m_original_data_bytes->push_back(cur->x);
            cur = m_huffmanTree.root;
            current = m_original_data_bytes->size();
            if (current == m_size) break;
        }
        if (!bit) cur = cur->lchild;
        else cur = cur->rchild;
    }
//    qDebug() << *m_original_data_bytes;
    current = m_size;
    state = DONE;
}

////// Getters //////
QByteArray HuffmanCompress::getOriginalBytes() {
    if (m_original_data_bytes == nullptr) decode();
    return *m_original_data_bytes;
}

QByteArray HuffmanCompress::getCompressedBytes() {
    if (m_compressed_data_bytes == nullptr) encode();
    return *m_compressed_data_bytes;
}

