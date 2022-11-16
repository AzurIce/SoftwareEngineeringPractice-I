#include "compressed_file.h"

#include <filesystem>
#include <QFile>
#include <QDir>
#include <QDebug>

CompressedFile::CompressedFile(QString p) {
    QFile fp(p);
    name = fp.fileName();

    QDir dir(p);
    if (dir.exists()) {
        isDir = true;
        for(auto& p: std::filesystem::recursive_directory_iterator(p.toStdWString())) {
            childs.push_back(CompressedFile(QString::fromStdWString(p.path().generic_wstring())));
        }
    } else {
        isDir = false;
        fp.open(QIODevice::ReadOnly);
        content = fp.readAll();
    }

//    qDebug() << name << isDir << content << childs.size();
}


QByteArray CompressedFile::toByte() {

}

CompressedFile CompressedFile::fromByte(QByteArray &arr) const {

}
