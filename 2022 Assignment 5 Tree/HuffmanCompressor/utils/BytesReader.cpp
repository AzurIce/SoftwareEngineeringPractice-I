//
// Created by AzurIce on 2022/11/17.
//

#include "utils/BytesReader.h"
#include <QDebug>

QByteArray BytesReader::readBytes() {

    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        current = 0;
        return {};
    }
    QDataStream rs(&file);

    QByteArray bytes;
    total = file.size();
    current = 0;
    char byte;
    for (int i = 1; i <= file.size(); i++) {
        rs >> byte;
        bytes.append(byte);
        current++;
    }

    return bytes;
}

QByteArray BytesReader::read() {
    return readBytes();
}
