#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "car_graphics_item.h"
#include "queue.h"
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void removeCar(GraphicsItemCar* car);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int n, m;

    void updateTime();
    void updateView();

    void init();

    void out();

    Queue<GraphicsItemCar*> inQueue;
    Queue<GraphicsItemCar*> outQueue;

protected:
        void timerEvent(QTimerEvent *event) override;
private:
    //定义需要用到的定时器
    int timer;
    int timerTime;
    int timerView;
    int timerOut;

    std::set<QString> mark;
};
#endif // MAINWINDOW_H
