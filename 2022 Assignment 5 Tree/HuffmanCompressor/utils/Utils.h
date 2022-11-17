//
// Created by AzurIce on 2022/11/10.
//

#ifndef HUFFMANCOMPRESSOR_QT_UTILS_H
#define HUFFMANCOMPRESSOR_QT_UTILS_H

#include <QByteArray>
#include <QString>
#include <QFile>
#include <QMap>
#include <vector>

class Utils {
public:
//    static QByteArray binaryStr2Bytes(const QString &str);
//    static QString bytes2BinaryStr(const QByteArray &bytes);
    static QByteArray bits2Bytes(const std::vector<bool> &bits);

    static std::vector<bool> bytes2Bits(const QByteArray &bytes);

    static void saveBytes(const QByteArray &bytes, const QString &path);

    static QByteArray readBytes(const QString &path);

    static QMap<char, unsigned int> getBytesHist(const QByteArray &bytes);

    static std::vector<bool> byte2Bits(const char &c);
};


#endif //HUFFMANCOMPRESSOR_QT_UTILS_H
