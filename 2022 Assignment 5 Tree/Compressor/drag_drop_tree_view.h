#ifndef DRAGANDDROPTREEVIEW_H
#define DRAGANDDROPTREEVIEW_H

#include <QTreeView>
#include <filesystem>

class DragDropTreeView : public QTreeView
{
    Q_OBJECT
public:
    DragDropTreeView(QWidget *parent);
    void addFile(QString &path);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // DRAGANDDROPTREEVIEW_H
