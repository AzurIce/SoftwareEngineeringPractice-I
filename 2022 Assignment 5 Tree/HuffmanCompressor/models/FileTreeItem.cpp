//
// Created by AzurIce on 2022/11/10.
//

#include "FileTreeItem.h"
#include "utils/Utils.h"

#include <QFileInfo>
#include <QDebug>
#include <QDir>


///// Constructor & deconstructor /////
// Construct from local path
FileTreeItem::FileTreeItem(const QString &path, FileTreeItem *parent) : m_parentItem(parent) {
    QFileInfo fileInfo(path);

    m_filename = fileInfo.fileName();
    m_isDir = fileInfo.isDir();

    m_itemData << m_filename;
    m_itemData << fileInfo.size();
    if (m_isDir) {
        QDir dir(path);
        for (const auto &f: dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
            appendChild(new FileTreeItem(f.filePath(), this));
        }
        for (auto child: m_childItems) {
            m_itemData[1] = m_itemData[1].toULongLong() + child->m_itemData[1].toULongLong();
        }
    } else {
        m_content = Utils::readBytes(path);
//        qDebug() << "Constructor read:" << m_content;
    }

}

///// Constructor Serializing /////
// File
FileTreeItem::FileTreeItem(const QString &filename, QByteArray &content, FileTreeItem *parent) :
        m_filename(filename), m_isDir(false), m_content(content), m_parentItem(parent) {
    m_itemData << filename << content.size();
}

// Dir
FileTreeItem::FileTreeItem(const QString &filename, QList<FileTreeItem *> &childItems, FileTreeItem *parent) :
        m_filename(filename), m_isDir(true), m_childItems(childItems), m_parentItem(parent) {
    m_itemData << filename << 0;
    for (auto child: m_childItems) {
        m_itemData[1] = m_itemData[1].toULongLong() + child->m_itemData[1].toULongLong();
    }
}

FileTreeItem::~FileTreeItem() {
    qDeleteAll(m_childItems);
}


///// Others /////
void FileTreeItem::appendChild(FileTreeItem *item) {
    m_childItems.append(item);
}


std::ostream &operator<<(std::ostream &os, const FileTreeItem &file) {
    os << "filename: " << file.m_filename.toLocal8Bit().data() << ", isDir: " << file.m_isDir
       << ", No Parent: " << (file.m_parentItem == nullptr) << ' ';

    if (file.m_isDir) {
        os << std::endl;
        for (auto child: file.m_childItems) {
            os << *child;
        }
    } else {
        os << ", filesize: " << file.m_content.size() << std::endl;
//        os << Utils::bytes2BinaryStr(file.m_content).toStdString() << std::endl;
    }
    return os;
}

QDataStream &operator<<(QDataStream &stream, const FileTreeItem &fileTreeItem) {
    stream << fileTreeItem.m_filename << fileTreeItem.m_isDir;
    if (fileTreeItem.m_isDir) {
        stream << (int) fileTreeItem.m_childItems.size();
        for (auto child: fileTreeItem.m_childItems) {
            stream << *child;
        }
    } else {
        stream << fileTreeItem.m_content;
    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, FileTreeItem &fileTreeItem) {
    stream >> fileTreeItem.m_filename >> fileTreeItem.m_isDir;
    if (fileTreeItem.m_isDir) {
        int childCount;
        stream >> childCount;
        while (childCount--) {
            FileTreeItem *item = new FileTreeItem(&fileTreeItem);
            fileTreeItem.appendChild(item);
            stream >> (*item);
        }
        fileTreeItem.m_itemData << fileTreeItem.m_filename << 0;
        for (auto child: fileTreeItem.m_childItems) {
            fileTreeItem.m_itemData[1] = fileTreeItem.m_itemData[1].toULongLong() + child->m_itemData[1].toULongLong();
        }
    } else {
        stream >> fileTreeItem.m_content;
        fileTreeItem.m_itemData << fileTreeItem.m_filename << fileTreeItem.m_content.size();
    }
    return stream;
}

/**
 * @brief CompressedFileItem::child
 * @param row
 * @return The child that corresponds to the specified row number in the item's list of child items
 */
FileTreeItem *FileTreeItem::child(int row) {
    if (row < 0 || row >= m_childItems.size()) return nullptr;
    return m_childItems.at(row);
}

QList<FileTreeItem *> FileTreeItem::getChilds() {
    return m_childItems;
}

unsigned long long FileTreeItem::childCount() const {
    return m_childItems.count();
}

/**
 * @brief CompressedFileItem::row
 * @return The item's location within its parent's list of items
 */
unsigned long long FileTreeItem::row() const {
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<FileTreeItem *>(this));

    return 0;
}

QVariant FileTreeItem::data(int column) const {
    if (column < 0 || column >= m_itemData.size()) return {};

    return m_itemData.at(column);
}


unsigned long long FileTreeItem::columnCount() const {
    return m_itemData.count();
}

FileTreeItem *FileTreeItem::parentItem() {
    return m_parentItem;
}

QByteArray FileTreeItem::toBytes() {
    QByteArray bytes;
    QDataStream ds(&bytes, QIODevice::ReadWrite); // 这里也可以跟 QFile关联
    ds << *this;
    return bytes;
}

FileTreeItem *FileTreeItem::fromBytes(QByteArray *bytes) {
    // 反序列化
    FileTreeItem *fileTreeItem = new FileTreeItem(nullptr);
    QDataStream rds(bytes, QIODevice::ReadOnly);
    rds >> *fileTreeItem;
    return fileTreeItem;
}

void FileTreeItem::setData(QList<QVariant> data) {
    m_itemData = data;
}

void FileTreeItem::setData() {
    setData({"Filename", "Size(Byte)"});
}

void FileTreeItem::setFileName(const QString &filename) {
    m_filename = filename;
}

void FileTreeItem::save(const QString &path) {
    for (auto child: m_childItems) {
        if (child->m_isDir) {
            QDir(path).mkdir(child->m_filename);
            QString target(path);
            child->save(target.append('/').append(child->m_filename));
        } else {
            QString target(path);
            Utils::saveBytes(child->m_content, target.append('/').append(child->m_filename));
        }
    }
}