//
// Created by AzurIce on 2022/11/10.
//

#include "FileTreeView.h"
#include "../models/FileTreeItemModel.h"
#include <QMimeData>

FileTreeView::FileTreeView(QWidget *parent) : QTreeView(parent) {
    setAcceptDrops(true);
    setDragDropMode(DragDropMode::DropOnly);
    setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

    connect(this, &FileTreeView::expanded, this, [=]() {
        resizeColumnToContents(0);
    });
    connect(this, &FileTreeView::collapsed, this, [=]() {
        resizeColumnToContents(0);
    });
    connect(this, &FileTreeView::doubleClicked, this, [=](const QModelIndex &index) {
        if (!static_cast<FileTreeItem *>(index.internalPointer())->isDir())
            emit extractAndOpenFile(static_cast<FileTreeItem *>(index.internalPointer()));
    });
//    setModel(new QStandardItemModel());
//    setModel(new CompressedFileItemModel("F:\\Syncthing\\Notes\\Coding\\Rust"));
//    setModel(new FileTreeItemModel());
//    expandAll();
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
    for (const auto &url: urls) {
        QString file_name = url.toLocalFile();
        ((FileTreeItemModel *) this->model())->addFile(file_name);
//        update();
    }
    resizeColumnToContents(0);
//    QAbstractItemView::dropEvent(event);
}

void FileTreeView::deleteSelected() {
    for (auto index:QTreeView::selectedIndexes()) {
        ((FileTreeItemModel *)model())->deleteAtIndex(index);
    }
}
void FileTreeView::saveSelected(const QString &path) {
    qDebug() << QTreeView::selectedIndexes();
    for (auto index:QTreeView::selectedIndexes()) {
        static_cast<FileTreeItem *>(index.internalPointer())->save(path);
    }
}