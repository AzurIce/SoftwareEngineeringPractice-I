#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include "models/InterestPointList.h"
#include "graphics/InterestPointGraphicsItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    public slots:
    void onSelect(int index);
    void onCheck(int index, bool checked);
private:
    Ui::MainWindow *ui;
    std::vector<InterestPointGraphicsItem *> interestPoints;
    InterestPointList interestPointList;
};
#endif // MAINWINDOW_H
