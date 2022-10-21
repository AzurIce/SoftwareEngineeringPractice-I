#ifndef CARQUEUEGRAPHICSVIEW_H
#define CARQUEUEGRAPHICSVIEW_H

#include <QGraphicsView>
#include "GraphicsItemCar.h"
#include "GraphicsItemGate.h"
#include "Queue.h"

class GraphicsViewCarQueue : public QGraphicsView
{
public:
    GraphicsViewCarQueue(QWidget *parent);
    ~GraphicsViewCarQueue();
    void test();
    void addCar(GraphicsItemCar *car);
private:
    Queue<GraphicsItemCar *> q;

    GraphicsItemGate* gate;
};

#endif // CARQUEUEGRAPHICSVIEW_H
