#ifndef COMPRESSED_FILE_H
#define COMPRESSED_FILE_H

#include <filesystem>
#include <QString>
#include <QByteArray>
#include <vector>

class CompressedFile {
public:
    CompressedFile(QString p);

    QByteArray toByte();
    CompressedFile fromByte(QByteArray &arr) const;
private:
    QString name;
    QByteArray content;
    bool isDir;
    std::vector<CompressedFile> childs;
};

#endif // COMPRESSED_FILE_H
