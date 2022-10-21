#include "GraphicsViewCarQueue.h"
#include "GraphicsItemCar.h"
#include "MyAnimation.h"

GraphicsViewCarQueue::GraphicsViewCarQueue(QWidget *parent): QGraphicsView(parent), gate(new GraphicsItemGate)
{
    setScene(new QGraphicsScene());
    gate->setPos(0, 0);
    setAlignment(Qt::AlignRight);
    scene()->addItem(gate);
}

GraphicsViewCarQueue::~GraphicsViewCarQueue()
{
    scene()->removeItem(gate);
    delete(gate);
}

void GraphicsViewCarQueue::addCar(GraphicsItemCar* car) {
    car->setPos(-width() - 5 - 4 - q.size() * (20 + 4) - 4, 0);
//    car->setPos(-q.size() * (20 + 4) - 5 - 4 - 2, 0);
    scene()->addItem(car);

//    MyAnimation *anim = new MyAnimation(car, "pos", this);
//    anim->setDuration(1000);
//    anim->setStartValue(QPoint(-width() - 5 - 4 - q.size() * (20 + 4), 0));
//    anim->setEndValue(QPoint(-q.size() * (20 + 4) - 5 - 4 - 2, 0));
//    anim->start();
    q.push(car);
//    qDebug() << q.size();
}

void GraphicsViewCarQueue::test() {
    MyAnimation *anim = new MyAnimation(gate, "pos", this);
    anim->setDuration(10000);
    anim->setStartValue(QPoint(0, 0));
    anim->setEndValue(QPoint(100, 250));
    anim->start();
}
