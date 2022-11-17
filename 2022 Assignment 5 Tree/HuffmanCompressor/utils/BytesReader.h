//
// Created by AzurIce on 2022/11/17.
//

#ifndef HUFFMANCOMPRESSOR_QT_BYTESREADER_H
#define HUFFMANCOMPRESSOR_QT_BYTESREADER_H

#include <atomic>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <thread>
#include <QThread>

class BytesReader {
public:
    BytesReader(const QString &path, std::atomic<int> &current, std::atomic<int> &total) :
            path(path), current(current), total(total) {};

    std::atomic<int> &current;
    std::atomic<int> &total;

    QByteArray read();

private:
    const QString path;

    QByteArray readBytes();
};


#endif //HUFFMANCOMPRESSOR_QT_BYTESREADER_H
