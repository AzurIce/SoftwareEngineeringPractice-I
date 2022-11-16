//
// Created by AzurIce on 2022/11/10.
//

#ifndef HUFFMANCOMPRESSOR_QT_FILETREEITEM_H
#define HUFFMANCOMPRESSOR_QT_FILETREEITEM_H

#include <QVariant>
#include <QString>
#include <QFile>

class FileTreeItem {
public:
    explicit FileTreeItem(): m_itemData({"Filename", "Size(Byte)"}), m_parentItem(nullptr) {};

    explicit FileTreeItem(FileTreeItem *parent): m_parentItem(parent) {};
    explicit FileTreeItem(const QString &path, FileTreeItem *parent = nullptr);

    explicit FileTreeItem(const QString &filename, QList<FileTreeItem *> &childItems, FileTreeItem *parent = nullptr);

    explicit FileTreeItem(const QString &filename, QByteArray &content, FileTreeItem *parent = nullptr);


    ~FileTreeItem();

    void appendChild(FileTreeItem *child);

    FileTreeItem *child(int row);

    void setData();
    void setData(QList<QVariant> data);
    void setFileName(const QString &filename);

    void save(const QString& path);

    QList<FileTreeItem *> getChilds();

    [[nodiscard]] unsigned long long childCount() const;

    [[nodiscard]] unsigned long long columnCount() const;

    [[nodiscard]] QVariant data(int column) const;

    [[nodiscard]] unsigned long long row() const;

    FileTreeItem *parentItem();

    QByteArray toBytes();

    static FileTreeItem *fromBytes(QByteArray *bytes);

    friend std::ostream &operator<<(std::ostream &os, const FileTreeItem &fileTreeItem);


    friend QDataStream &operator<<(QDataStream &stream, const FileTreeItem &fileTreeItem);

    friend QDataStream &operator>>(QDataStream &stream, FileTreeItem &fileTreeItem);

private:
    QList<QVariant> m_itemData;
    FileTreeItem *m_parentItem;

    // Need to be Serialized
    QList<FileTreeItem *> m_childItems; // Should Serialize the corresponding object but not pointer
    QByteArray m_content;
    QString m_filename;
    bool m_isDir;
};


#endif //HUFFMANCOMPRESSOR_QT_FILETREEITEM_H
