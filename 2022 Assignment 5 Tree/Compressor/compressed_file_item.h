#ifndef COMPRESSEDFILEITEM_H
#define COMPRESSEDFILEITEM_H

#include <QVariant>
#include <QFile>

class CompressedFileItem
{
public:
    explicit CompressedFileItem(QString path, CompressedFileItem *parent);
    explicit CompressedFileItem(const QList<QVariant> &data, CompressedFileItem *parentItem = nullptr);
    ~CompressedFileItem();

    void appendChild(CompressedFileItem *child);

    CompressedFileItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    CompressedFileItem *parentItem();

    QByteArray encode(std::map<char, QByteArray> codingmap);
private:
    QList<CompressedFileItem *> m_childItems;
    QList<QVariant> m_itemData;
    CompressedFileItem *m_parentItem;
};

#endif // COMPRESSEDFILEITEM_H
