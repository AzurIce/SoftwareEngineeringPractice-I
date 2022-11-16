#include "compressed_file_item.h"

#include <QFileInfo>
#include <QDebug>
#include <QDir>

CompressedFileItem::CompressedFileItem(QString path, CompressedFileItem *parent): m_parentItem(parent) {
    QFileInfo fileInfo(path);

    QString name = fileInfo.fileName(); //
    bool isDir = fileInfo.isDir();     //
    m_itemData << name;
    if (isDir) {
        m_itemData << fileInfo.size();
        QDir dir(path);
        for (auto f: dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
            qDebug() << "processing:" << f.filePath();
            appendChild(new CompressedFileItem(f.filePath(), this));
        }
    }else {
        m_itemData << fileInfo.size();

        QFile fp(path);
        fp.open(QIODevice::ReadOnly);
        QByteArray content = fp.readAll(); //
    }

    for (auto child: m_childItems) {
        m_itemData[1] = m_itemData[1].toULongLong() + child->m_itemData[1].toULongLong();
    }
}

///// Constructor & deconstructor /////
CompressedFileItem::CompressedFileItem(const QList<QVariant> &data, CompressedFileItem *parent)
    : m_itemData(data), m_parentItem(parent) {}

CompressedFileItem::~CompressedFileItem() {
    qDeleteAll(m_childItems);
}


///// Others /////
void CompressedFileItem::appendChild(CompressedFileItem *item) {
    m_childItems.append(item);
}

/**
 * @brief CompressedFileItem::child
 * @param row
 * @return The child that corresponds to the specified row number in the item's list of child items
 */
CompressedFileItem *CompressedFileItem::child(int row) {
    if (row < 0 || row >= m_childItems.size()) return nullptr;
    return m_childItems.at(row);
}

int CompressedFileItem::childCount() const {
    return m_childItems.count();
}

/**
 * @brief CompressedFileItem::row
 * @return The item's location within its parent's list of items
 */
int CompressedFileItem::row() const {
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<CompressedFileItem*>(this));

    return 0;
}

QVariant CompressedFileItem::data(int column) const {
    if (column < 0 || column >= m_itemData.size()) return QVariant();

    return m_itemData.at(column);
}


int CompressedFileItem::columnCount() const {
    return m_itemData.count();
}

CompressedFileItem *CompressedFileItem::parentItem() {
    return m_parentItem;
}
