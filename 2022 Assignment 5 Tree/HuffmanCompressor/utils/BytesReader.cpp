//
// Created by AzurIce on 2022/11/17.
//

#include "utils/BytesReader.h"
#include <QDebug>

QByteArray BytesReader::readBytes() {
    QByteArray bytes;

//    reading = true;
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
//        reading = false;
        current = 0;
        return bytes;
    }
    QDataStream rs(&file);

    total = file.size();
    current = 0;
    char byte;
    for (int i = 1; i <= file.size(); i++) {
        rs >> byte;
        bytes.append(byte);
        current++;
    }

//    reading = false;
    return bytes;
}

QByteArray BytesReader::read() {
    return readBytes();
//    QThread *t = QThread::create(&BytesSaver::writeBytes, this);
//    t->start();
}
