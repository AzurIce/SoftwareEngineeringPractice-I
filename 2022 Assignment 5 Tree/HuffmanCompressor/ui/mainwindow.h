#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "models/FileTreeItemModel.h"
#include "libs/HuffmanCompress.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *event) override;
private:
    Ui::MainWindow *ui;
    FileTreeItemModel *model;
    HuffmanCompress *compress;
//    QProgressDialog *progress;

    int timer;
};
#endif // MAINWINDOW_H
