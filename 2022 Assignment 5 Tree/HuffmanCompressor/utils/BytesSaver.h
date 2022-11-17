//
// Created by AzurIce on 2022/11/17.
//

#ifndef HUFFMANCOMPRESSOR_QT_BYTESSAVER_H
#define HUFFMANCOMPRESSOR_QT_BYTESSAVER_H

#include <atomic>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <thread>
#include <QThread>

class BytesSaver {
public:
    BytesSaver(const QByteArray &bytes, const QString &path, std::atomic<int> &current, std::atomic<int> &total) :
            bytes(bytes), path(path), current(current), total(total) {};

    std::atomic<int> &current;
    std::atomic<int> &total;

    void save();

private:
    const QByteArray bytes;
    const QString path;

    void writeBytes();
};


#endif //HUFFMANCOMPRESSOR_QT_BYTESSAVER_H
