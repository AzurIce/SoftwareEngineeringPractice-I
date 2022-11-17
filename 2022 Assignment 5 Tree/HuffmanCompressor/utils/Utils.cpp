//
// Created by AzurIce on 2022/11/10.
//

#include "Utils.h"

#include <QByteArray>
#include <QString>
#include <QFile>
#include <QDebug>

void Utils::saveBytes(const QByteArray &bytes, const QString &path) {
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(bytes);
}

QByteArray Utils::readBytes(const QString &path) {
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    return file.readAll();
}

//QByteArray Utils::binaryStr2Bytes(const QString &str) {
//    QByteArray bytes;
//    for (int i = 0; i < str.size() / 8; i++) {
//        int byte = 0;
//        for (int j = 0; j < 8; j++) {
//            byte = byte << 1 | str.at(i * 8 + j).toLatin1() - '0';
//        }
//        bytes.append((char) byte);
////        qDebug() << "byte:" << byte;
//    }
//    if (str.size() % 8) {
//        int byte = 0;
//        int i = str.size() / 8;
//        for (int j = 0; j < 8; j++) {
//            if (i * 8 + j < str.size()) byte = byte << 1 | str.at(i * 8 + j).toLatin1() - '0';
//            else byte <<= 1;
//        }
////        qDebug() << "rest:" << byte;
//        bytes.append((char) byte);
//    }
//
////    qDebug() << "bytes:" << bytes;
//    return bytes;
//}
//
//QString Utils::bytes2BinaryStr(const QByteArray &bytes) {
//    QString str;
//    for (char byte: bytes) {
////        qDebug() << (int)byte;
//        for (int i = 7; i >= 0; i--) {
////            qDebug() << (byte & (1 << i));
//            str.append(QString::number((int) ((byte & (1 << i)) != 0)));
//        }
////        qDebug() << str;
//    }
//    return str;
//}

QByteArray Utils::bits2Bytes(const std::vector<bool> &bits) {
    QByteArray bytes;
    for (int i = 0; i < bits.size() / 8; i++) {
        int byte = 0;
        for (int j = 0; j < 8; j++) {
            byte = byte << 1 | bits[i * 8 + j];
        }
        bytes.append((char) byte);
    }
    if (bits.size() % 8) {
        int byte = 0;
        unsigned long long i = bits.size() / 8;
        for (int j = 0; j < 8; j++) {
            if (i * 8 + j < bits.size()) byte = byte << 1 | bits[i * 8 + j];
            else byte <<= 1;
        }
        bytes.append((char) byte);
    }

    return bytes;
}

std::vector<bool> Utils::bytes2Bits(const QByteArray &bytes) {
    std::vector<bool> bits;
    for (char byte: bytes) {
        for (int i = 7; i >= 0; i--) {
            bits.push_back((byte & (1 << i)) != 0);
        }
    }
    return bits;
}

QMap<char, unsigned int> Utils::getBytesHist(const QByteArray &bytes) {
    QMap<char, unsigned int> byteHist;
    for (int i = 0; i < 1 << 8; i++) {
        if (bytes.count((char) i)) {
            byteHist[(char) i] = bytes.count((char) i);
        }
    }
    return byteHist;
}

std::vector<bool> Utils::byte2Bits(const char &byte) {
    std::vector<bool> bits;
    for (int i = 7; i >= 0; i--) {
        bits.push_back((byte & (1 << i)) != 0);
    }
    return bits;
}
