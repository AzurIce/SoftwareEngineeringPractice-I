//
// Created by AzurIce on 2022/11/10.
//

#ifndef HUFFMANCOMPRESSOR_QT_HUFFMANCOMPRESS_H
#define HUFFMANCOMPRESSOR_QT_HUFFMANCOMPRESS_H


#include <QByteArray>
#include <QMap>
#include "HuffmanTree.h"
#include <QProgressDialog>
#include <atomic>

class HuffmanCompress {
public:
    enum State {
        INIT, ENCODING, COMPRESSING, DECOMPRESSING, DONE
    };

    ////// Constructors and destructors //////
    explicit HuffmanCompress(std::atomic<int> &current, std::atomic<int> &total) : current(current), total(total) {};

    explicit HuffmanCompress(const QByteArray &bytes, std::atomic<int> &current, std::atomic<int> &total);

    ~HuffmanCompress();

    ////// Serializing and Deserializing //////
    QByteArray toBytes();

    static HuffmanCompress *fromBytes(QByteArray *bytes, std::atomic<int> &current, std::atomic<int> &total);

    ////// Getters //////
    std::atomic<int> &current;
    std::atomic<int> &total;
    std::atomic<State> state = INIT;

    QByteArray getOriginalBytes();

    QByteArray getCompressedBytes();

private:
    void encode();

    void decode();

    int m_size = 0;                     // Serialized
    HuffmanTree m_huffmanTree;          // Serialized(See HuffmanTree)
    QByteArray *m_original_data_bytes = nullptr;
    QByteArray *m_compressed_data_bytes = nullptr; // Serialized
};


#endif //HUFFMANCOMPRESSOR_QT_HUFFMANCOMPRESS_H
