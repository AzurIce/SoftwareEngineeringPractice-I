#include "compress_file_item_model.h"

#include <QFileSystemModel>

CompressFileItemModel::CompressFileItemModel(QObject *parent)
    : QAbstractItemModel{parent}
{
    QFileSystemModel();
}
