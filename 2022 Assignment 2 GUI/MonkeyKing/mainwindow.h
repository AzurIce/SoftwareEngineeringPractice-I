#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cyclelinkedlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void debugPrint(const QString &text);
    void debugPrint(int x);

private slots:
    void on_btnStart_clicked();

    void on_btnStep_clicked();

private:
    Ui::MainWindow *ui;
    CycleLinkedList list;
    CycleLinkedListNode* p;
    int n;
    int k;
};
#endif // MAINWINDOW_H
