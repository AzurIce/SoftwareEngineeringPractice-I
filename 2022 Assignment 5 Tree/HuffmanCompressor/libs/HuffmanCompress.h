//
// Created by AzurIce on 2022/11/10.
//

#ifndef HUFFMANCOMPRESSOR_QT_HUFFMANCOMPRESS_H
#define HUFFMANCOMPRESSOR_QT_HUFFMANCOMPRESS_H


#include <QByteArray>
#include <QMap>
#include "HuffmanTree.h"
#include <QProgressDialog>

class HuffmanCompress{
public:
    enum State {
        INITIALIZED, COMPRESSING, DECOMPRESSING, DONE
    };
    State state;

    ////// Constructors and destructors //////
    HuffmanCompress(): m_size(0), state(INITIALIZED){};
    explicit HuffmanCompress(const QByteArray &bytes);
    ~HuffmanCompress();

    ////// Serializing and Deserializing //////
    [[nodiscard]] QByteArray toBytes() const;
    static HuffmanCompress *fromBytes(QByteArray *bytes);

    friend QDataStream &operator<<(QDataStream &stream, const HuffmanCompress &huffmanCompress);
    friend QDataStream &operator>>(QDataStream &stream, HuffmanCompress &huffmanCompress);

    ////// Getters //////
    int getOriginalSize();
    int getTotal();
    int getCurrent();
    QByteArray getOriginalBytes();
    QByteArray getCompressedBytes();
private:
    HuffmanTree m_huffmanTree;          // Serialized(See HuffmanTree)
    unsigned long long m_size;          // Serialized
    QByteArray m_original_data_bytes;
    QByteArray m_compressed_data_bytes; // Serialized
};


#endif //HUFFMANCOMPRESSOR_QT_HUFFMANCOMPRESS_H
