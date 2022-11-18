#include "parking_slot_graphics_item.h"
//#include "AnimationCar.h"
//#include "GraphicsViewCarPark.h"

GraphicsItemParkingSlot::GraphicsItemParkingSlot(int index): index(index), car(nullptr) {
    pen = QPen(QBrush(QColor(100, 100, 100)), 0.5);
    QList<qreal> dashes;

    dashes << 6 << 4;
    pen.setDashPattern(dashes);
}

QRectF GraphicsItemParkingSlot::boundingRect() const {
    return QRectF(-5, -10, 10, 20);
}

void GraphicsItemParkingSlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
//    painter->setBrush(QColor(100, 100, 100));

    painter->setFont(QFont("Consolas", 4));
    painter->setPen(QPen(QBrush(QColor(100, 100, 100)), 0.5));
    painter->drawText(-5 + 1, -10 + 1, 10 - 2, 20 - 2, Qt::AlignCenter, QString::number(index));

    painter->setPen(pen);
    painter->drawRect(-5 + 1, -10 + 1, 10 - 2, 20 - 2);

}

//void GraphicsItemParkingSlot::mousePressEvent(QGraphicsSceneMouseEvent *event) {
//    if (!isEmpty()) {
//        AnimationCar* anim = new AnimationCar(this, (GaphicsSceneCarPark *)scene(), total, index, total+1);
//        anim->setDuration(1000);
//        anim->start();
//    }
//    update();
//}
