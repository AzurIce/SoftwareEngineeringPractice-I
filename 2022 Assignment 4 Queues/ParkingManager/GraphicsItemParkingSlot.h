#ifndef PARKINGSLOTGRAPHICSITEM_H
#define PARKINGSLOTGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include "GraphicsItemCar.h"

class GraphicsItemParkingSlot : public QGraphicsItem
{
public:
    GraphicsItemParkingSlot(int index);
    GraphicsItemCar* getCar() {
        return car;
    }
    void setCar(GraphicsItemCar* car) {
        this->car = car;
    }
    bool isEmpty() {
        return car == nullptr;
    }
    int getIndex() {
        return index;
    }
private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QPen pen;
    int index;
//    int total;
    GraphicsItemCar* car;
};

#endif // PARKINGSLOTGRAPHICSITEM_H
