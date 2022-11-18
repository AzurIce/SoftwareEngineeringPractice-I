//
// Created by AzurIce on 2022/11/10.
//

#include "FileTreeItemModel.h"
#include "FileTreeItem.h"
#include <QFileInfo>
#include <QFile>

FileTreeItemModel::FileTreeItemModel(QObject *parent) : QAbstractItemModel(parent) {
    rootItem = new FileTreeItem();
}


FileTreeItemModel::FileTreeItemModel(FileTreeItem *rootItem, QObject *parent) {
    this->rootItem = rootItem;
    rootItem->setData();
    parent = parent;
}

FileTreeItemModel::FileTreeItemModel(const QString &path, QObject *parent) : QAbstractItemModel(parent) {
    rootItem = new FileTreeItem();

    qDebug() << "Setting up model data...";
    ((FileTreeItem *) parent)->appendChild(new FileTreeItem(path, (FileTreeItem *) parent));
    qDebug() << "Done.";
}

FileTreeItemModel::~FileTreeItemModel() {
    delete rootItem;
}


QModelIndex FileTreeItemModel::index(int row, int column) const {
    return index(row, column, QModelIndex());
}

QModelIndex FileTreeItemModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    FileTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<FileTreeItem *>(parent.internalPointer());

    FileTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex FileTreeItemModel::parent(const QModelIndex &index) const {
    if (!index.isValid())
        return QModelIndex();

    FileTreeItem *childItem = static_cast<FileTreeItem *>(index.internalPointer());
    FileTreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int FileTreeItemModel::rowCount(const QModelIndex &parent) const {
    FileTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<FileTreeItem *>(parent.internalPointer());

    return parentItem->childCount();
}

int FileTreeItemModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return static_cast<FileTreeItem *>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QVariant FileTreeItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();

    FileTreeItem *item = static_cast<FileTreeItem *>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags FileTreeItemModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant FileTreeItemModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

void FileTreeItemModel::addFile(const QString &path) {
    qDebug() << "Adding file:" << path;
    beginInsertRows(QModelIndex(), rowCount() - 1, rowCount() - 1);
    rootItem->appendChild(new FileTreeItem(path, rootItem));
    endInsertRows();
}

void FileTreeItemModel::deleteAtIndex(QModelIndex index) {
    beginRemoveRows(index.parent(), index.row(), index.row());
    static_cast<FileTreeItem *>(index.parent().internalPointer())->removeChild(
            static_cast<FileTreeItem *>(index.internalPointer()));
    endRemoveRows();
}

FileTreeItem *FileTreeItemModel::itemFromIndex(const QModelIndex &index) {
    return static_cast<FileTreeItem *>(index.internalPointer());
}

int FileTreeItemModel::rowCount() const {
    return rowCount(QModelIndex());
}

int FileTreeItemModel::columnCount() const {
    return columnCount(QModelIndex());
}

FileTreeItem *FileTreeItemModel::getRootItem() {
    return rootItem;
}

void FileTreeItemModel::setRootItem(FileTreeItem *item) {
    delete rootItem;
    rootItem = new FileTreeItem();
    auto childs = item->getChilds();
    beginInsertRows(QModelIndex(), 0, childs.size());
    for (auto child: childs) {
        rootItem->appendChild(child);
    }
    endInsertRows();
//    rootItem = item;
}



