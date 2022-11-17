//
// Created by AzurIce on 2022/11/10.
//

#ifndef HUFFMANCOMPRESSOR_QT_FILETREEITEMMODEL_H
#define HUFFMANCOMPRESSOR_QT_FILETREEITEMMODEL_H

#include <QAbstractItemModel>
#include "FileTreeItem.h"

class FileTreeItemModel : public QAbstractItemModel {
Q_OBJECT
public:
    explicit FileTreeItemModel(QObject *parent = nullptr);

    explicit FileTreeItemModel(FileTreeItem *rootItem, QObject *parent = nullptr);

    explicit FileTreeItemModel(const QString &data, QObject *parent = nullptr);

    ~FileTreeItemModel();

    // Returns the data stored under the given role for the item referred to by the index.
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    // Default: Qt::ItemIsEnabled | Qt::ItemIsSelectable
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Returns the data for the given role and section in the header with the specified orientation.
    [[nodiscard]] QVariant
    headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex &parent) const override;

    [[nodiscard]] QModelIndex index(int row, int column) const;

    [[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] int rowCount() const;

    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

    [[nodiscard]] int columnCount() const;

    void addFile(const QString &path);

    static FileTreeItem *itemFromIndex(const QModelIndex &index);

    FileTreeItem *getRootItem();

    void setRootItem(FileTreeItem *item);

    void deleteAtIndex(QModelIndex index);


private:
    FileTreeItem *rootItem;
};


#endif //HUFFMANCOMPRESSOR_QT_FILETREEITEMMODEL_H
