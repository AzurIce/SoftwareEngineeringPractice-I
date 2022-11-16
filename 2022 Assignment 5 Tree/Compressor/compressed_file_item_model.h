#ifndef COMPRESSEDFILEITEMMODEL_H
#define COMPRESSEDFILEITEMMODEL_H

#include <QAbstractItemModel>
#include "compressed_file_item.h"

class CompressedFileItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit CompressedFileItemModel(QObject *parent = nullptr);
    explicit CompressedFileItemModel(const QString &data, QObject *parent = nullptr);
    ~CompressedFileItemModel();

    // Returns the data stored under the given role for the item referred to by the index.
    QVariant data(const QModelIndex &index, int role) const override;

    // Default: Qt::ItemIsEnabled | Qt::ItemIsSelectable
    Qt::ItemFlags flags(const QModelIndex &index) const override;\
    // Returns the data for the given role and section in the header with the specified orientation.
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;


    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void addFile(const QString &path);

    CompressedFileItem *itemFromIndex(const QModelIndex &index);

private:
    void setupModelData(const QString &path, CompressedFileItem *parent);

    CompressedFileItem *rootItem;
};


#endif // COMPRESSEDFILEITEMMODEL_H
