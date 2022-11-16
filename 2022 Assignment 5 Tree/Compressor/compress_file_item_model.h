#ifndef COMPRESSFILEITEMMODEL_H
#define COMPRESSFILEITEMMODEL_H

#include <QAbstractItemModel>

class CompressFileItemModel : public QAbstractItemModel
{
public:
    explicit CompressFileItemModel(QObject *parent = nullptr);
};

#endif // COMPRESSFILEITEMMODEL_H
