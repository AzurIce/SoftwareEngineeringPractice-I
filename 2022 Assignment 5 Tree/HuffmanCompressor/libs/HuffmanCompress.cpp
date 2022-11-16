//
// Created by AzurIce on 2022/11/10.
//

#include "HuffmanCompress.h"
#include "utils/utils.h"
#include <iostream>
#include <QDebug>

////// Constructors and destructors //////
// Construct from original data bytes
HuffmanCompress::HuffmanCompress(const QByteArray &bytes) : state(INITIALIZED) {
    m_original_data_bytes = bytes;
    m_size = bytes.size();

    state = COMPRESSING;
    m_huffmanTree.init(Utils::getBytesHist(bytes));
    m_compressed_data_bytes = m_huffmanTree.encode(m_original_data_bytes);
    state = DONE;
}

HuffmanCompress::~HuffmanCompress() {
}

////// Serializing and Deserializing //////
/*
 * Serialize and Deserialize will use compressed data bytes
 */

// Serialize
QDataStream &operator<<(QDataStream &stream, const HuffmanCompress &huffmanCompress) {
    stream << huffmanCompress.m_huffmanTree
           << huffmanCompress.m_size
           << huffmanCompress.m_compressed_data_bytes;
    return stream;
}

QByteArray HuffmanCompress::toBytes() const {
    QByteArray bytes;
    QDataStream ds(&bytes, QIODevice::ReadWrite); // 这里也可以跟 QFile关联
    ds << *this;
    return bytes;
}

// DeSerialize
QDataStream &operator>>(QDataStream &stream, HuffmanCompress &compress) {
    stream >> compress.m_huffmanTree
           >> compress.m_size
           >> compress.m_compressed_data_bytes;


    return stream;
}

HuffmanCompress *HuffmanCompress::fromBytes(QByteArray *bytes) {
    auto *compress = new HuffmanCompress();
    QDataStream rds(bytes, QIODevice::ReadOnly);
    rds >> *compress;
    compress->m_original_data_bytes = compress->m_huffmanTree.decode(compress->m_compressed_data_bytes, compress->m_size);
    return compress;
}

////// Getters //////
QByteArray HuffmanCompress::getOriginalBytes() {
    return m_original_data_bytes;
}
QByteArray HuffmanCompress::getCompressedBytes() {
    return m_compressed_data_bytes;
}

int HuffmanCompress::getOriginalSize() {
    return m_size;
}

int HuffmanCompress::getTotal() {
    return m_huffmanTree.total;
}

int HuffmanCompress::getCurrent() {
    return m_huffmanTree.current;
}

