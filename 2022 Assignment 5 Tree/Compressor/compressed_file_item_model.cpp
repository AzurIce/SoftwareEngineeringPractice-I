#include "compressed_file_item_model.h"

#include "compressed_file_item.h"
#include <QFileInfo>
#include <QFile>

CompressedFileItemModel::CompressedFileItemModel(QObject *parent)
    : QAbstractItemModel(parent) {
    rootItem = new CompressedFileItem({tr("Filename"), tr("Size(Byte)")}, nullptr);
}

CompressedFileItemModel::CompressedFileItemModel(const QString &path, QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new CompressedFileItem({tr("Filename"), tr("Size(Byte)")}, nullptr);
    setupModelData(path, rootItem);
}

CompressedFileItemModel::~CompressedFileItemModel()
{
    delete rootItem;
}

QModelIndex CompressedFileItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    CompressedFileItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<CompressedFileItem*>(parent.internalPointer());

    CompressedFileItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex CompressedFileItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    CompressedFileItem *childItem = static_cast<CompressedFileItem*>(index.internalPointer());
    CompressedFileItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int CompressedFileItemModel::rowCount(const QModelIndex &parent) const {
    CompressedFileItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<CompressedFileItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int CompressedFileItemModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return static_cast<CompressedFileItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QVariant CompressedFileItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();

    CompressedFileItem *item = static_cast<CompressedFileItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags CompressedFileItemModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant CompressedFileItemModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

void CompressedFileItemModel::setupModelData(const QString &path, CompressedFileItem *parent)
{
    qDebug() << "Setting up model data...";
    parent->appendChild(new CompressedFileItem(path, parent));
    qDebug() << "Done.";
}

void CompressedFileItemModel::addFile(const QString &path) {
    qDebug() << "Adding file:" << path;
    beginInsertRows(QModelIndex(), rowCount() - 1, rowCount() - 1);
    rootItem->appendChild(new CompressedFileItem(path, rootItem));
    endInsertRows();
}


CompressedFileItem *CompressedFileItemModel::itemFromIndex(const QModelIndex &index) {
    return static_cast<CompressedFileItem*>(index.internalPointer());
}

