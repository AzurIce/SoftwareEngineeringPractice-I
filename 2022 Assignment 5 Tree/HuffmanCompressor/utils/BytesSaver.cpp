//
// Created by AzurIce on 2022/11/17.
//

#include "BytesSaver.h"
#include <QDebug>

void BytesSaver::writeBytes() {
//    saving = true;
    QFile file(path);
    if (!file.open(QFile::WriteOnly)) return;
    QDataStream ws(&file);

    total = file.size();
    for (char byte: bytes) {
        ws << byte;
        current++;
    }
//    saving = false;
}

void BytesSaver::save() {
    writeBytes();
//    QThread *t = QThread::create(&BytesSaver::writeBytes, this);
//    t->start();
}
