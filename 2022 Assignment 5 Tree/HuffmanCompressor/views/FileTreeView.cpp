//
// Created by AzurIce on 2022/11/10.
//

#include "FileTreeView.h"
#include "../models/FileTreeItemModel.h"
#include <QMimeData>

FileTreeView::FileTreeView(QWidget *parent) : QTreeView(parent) {
    setAcceptDrops(true);
    setDragDropMode(DragDropMode::DropOnly);
//    setModel(new QStandardItemModel());
//    setModel(new CompressedFileItemModel("F:\\Syncthing\\Notes\\Coding\\Rust"));
//    setModel(new FileTreeItemModel());
//    expandAll();
    setColumnWidth(0, 300);
}

void FileTreeView::addFile(QString &path) {

}

void FileTreeView::dragEnterEvent(QDragEnterEvent *event) {
    event->setAccepted(true);
    event->acceptProposedAction();
//    QAbstractItemView::dragEnterEvent(event);
}

void FileTreeView::dragMoveEvent(QDragMoveEvent *event) {
    event->setAccepted(true);
    event->acceptProposedAction();
//    QTreeView::dragMoveEvent(event);
}

void FileTreeView::dropEvent(QDropEvent *event) {
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;

    qDebug() << "View - dropEvent - Adding Files: " << urls;
    for (auto url: urls) {
        QString file_name = url.toLocalFile();
        ((FileTreeItemModel *) this->model())->addFile(file_name);
//        update();
    }
//    QAbstractItemView::dropEvent(event);
}
