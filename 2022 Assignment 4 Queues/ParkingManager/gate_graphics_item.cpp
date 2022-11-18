#include "GraphicsItemGate.h"

GraphicsItemGate::GraphicsItemGate(): enabled(false) {

}

QRectF GraphicsItemGate::boundingRect() const {
    return QRectF(-2, -20, 4, 40);
}

void GraphicsItemGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
//    qDebug() << "paint";
    if (enabled) {
        painter->setBrush(QColor(100, 200, 100));
    } else {
        painter->setBrush(QColor(200, 100, 100));
    }
    painter->drawRect(boundingRect());
    painter->setBrush(Qt::NoBrush);
}

void GraphicsItemGate::mousePressEvent(QGraphicsSceneMouseEvent *event) {
//    qDebug() << "???";
    enabled = !enabled;
    update();
}
