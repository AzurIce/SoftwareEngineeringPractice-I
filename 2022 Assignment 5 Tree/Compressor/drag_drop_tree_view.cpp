#include "drag_drop_tree_view.h"

#include <QDebug>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QStandardItemModel>
#include <filesystem>
#include <iostream>
#include <stack>
#include <cstring>

#include "compressed_file_item.h"
#include "compressed_file_item_model.h"

DragDropTreeView::DragDropTreeView(QWidget *parent): QTreeView(parent)
{
    setAcceptDrops(true);
    setDragDropMode(DragDropMode::DropOnly);
//    setModel(new QStandardItemModel());
//    setModel(new CompressedFileItemModel("F:\\Syncthing\\Notes\\Coding\\Rust"));
    setModel(new CompressedFileItemModel());
    expandAll();
    setColumnWidth(0, 300);
}


void DragDropTreeView::dragEnterEvent(QDragEnterEvent *event) {
    event->setAccepted(true);
    event->acceptProposedAction();
}

void DragDropTreeView::dragMoveEvent(QDragMoveEvent *event) {
    event->setAccepted(true);
    event->acceptProposedAction();
}

void DragDropTreeView::addFile(QString &path) {
//    CompressedFileItemModel *model = (CompressedFileItemModel *)(this->model());
//    model->addFile(path, parent);
//    std::stack<QStandardItem*> parentStack;
//    std::stack<std::filesystem::path> parentPathStack;

////    QStandardItemModel *model = (QStandardItemModel *)(this->model());
//    QStandardItemModel *model = (QStandardItemModel *)(this->model());
//    parentStack.push(model->invisibleRootItem());

//    QStandardItem *fileItem = new QStandardItem(QString::fromStdWString(p.generic_wstring()));
//    parentStack.top()->appendRow(fileItem);
//    parentStack.push(fileItem);
//    parentPathStack.push(p);

//    for(auto& p: std::filesystem::recursive_directory_iterator(p)) {
////            qDebug() << "Cur Path:" << QString::fromStdWString(p.path().generic_wstring());
//        QStandardItem *item = new QStandardItem(QString::fromStdWString(p.path().filename().generic_wstring()));
//        while (p.path().parent_path().compare(parentPathStack.top())) {
////                qDebug() << "parent_path():" << p.path().parent_path().generic_wstring();
////                qDebug() << "parenPathStack.top():" <<  parentPathStack.top().generic_wstring();
//            parentStack.pop();
//            parentPathStack.pop();
//        }
//        parentStack.top()->appendRow(item);
//        if (p.is_directory()) {
//            parentStack.push(item);
//            parentPathStack.push(p.path());
//        }
//    }
}

void DragDropTreeView::dropEvent(QDropEvent *event) {

    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;

    qDebug() << "View - dropEvent - Adding Files: " << urls;
    for(auto url: urls) {
        QString file_name = url.toLocalFile();
        ((CompressedFileItemModel *)this->model())->addFile(file_name);
//        update();
    }

//    expandAll();
}
