#ifndef CARGRAPHICSITEM_H
#define CARGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsView>
#include "queue.h"

class GraphicsItemCar : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GraphicsItemCar(QString license, int index);

    void setPath(QPainterPath* path);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void updateInTime();
    void updateOutTime();

    double cauculateCost();
    QString getLicense();
    time_t getTimeIn();
    time_t getTimeOut();
    QString getCTimeIn();
    QString getCTimeOut();
    int getIndex();

protected:
    void advance(int step) override;

signals:
    void removeCar(GraphicsItemCar* car);
    void movementFinished(GraphicsItemCar* car);

private:
    ///// Movement /////
    QPainterPath* path; // Current moving path
    qreal pathProgress; // Current progress of movement on the path
    QPointF speed;
    qreal angle;

    ///// park attribute /////
    QString license;
    time_t time_in;
    long long tick_stay;
    time_t time_out;
    QString ctime_in;
    QString ctime_out;
    int index;
};

template<>
QString Queue<GraphicsItemCar *>::toString();

#endif // CARGRAPHICSITEM_H
