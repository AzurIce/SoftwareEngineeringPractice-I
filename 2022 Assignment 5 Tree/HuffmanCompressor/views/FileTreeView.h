//
// Created by xiaob on 2022/11/10.
//

#ifndef HUFFMANCOMPRESSOR_QT_FILETREEVIEW_H
#define HUFFMANCOMPRESSOR_QT_FILETREEVIEW_H

#include <QTreeView>
#include <QString>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include "models/FileTreeItem.h"

class FileTreeView : public QTreeView {
Q_OBJECT
public:
    explicit FileTreeView(QWidget *parent);

    void addFile(QString &path);
    void deleteSelected();
    void saveSelected(const QString &path);
signals:
    void extractAndOpenFile(FileTreeItem *item);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;

    void dragMoveEvent(QDragMoveEvent *event) override;

    void dropEvent(QDropEvent *event) override;
};


#endif //HUFFMANCOMPRESSOR_QT_FILETREEVIEW_H
