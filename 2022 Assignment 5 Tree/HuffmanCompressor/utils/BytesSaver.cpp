//
// Created by AzurIce on 2022/11/17.
//

#include "BytesSaver.h"
#include <QDebug>

void BytesSaver::writeBytes() {
    QFile file(path);
    if (!file.open(QFile::WriteOnly)) return;
    QDataStream ws(&file);

    total = file.size();
    for (char byte: bytes) {
        ws << byte;
        current++;
    }
}

void BytesSaver::save() {
    writeBytes();
}
