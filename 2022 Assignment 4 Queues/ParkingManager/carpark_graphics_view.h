#ifndef CARPARKGRAPHICSVIEW_H
#define CARPARKGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QPainterPath>
#include <vector>
#include "parking_slot_graphics_item.h"

#define MAX_SIZE 128

class GraphicsViewCarPark : public QGraphicsView
{
    Q_OBJECT
signals:
    void outCar(GraphicsItemCar* car);
public:
    GraphicsViewCarPark(QWidget *parent);

    QPainterPath *generatePath(int src, int dst); // Generate a path from src to dst. 0 for entrance, n+1 for exit.

    void init(int n, int m);
//    void addCar(GraphicsItemCar* car);
    QPointF getPos(int index);
    QPointF getPathPos(int index);
    int getRow(int index);
    int getCol(int index);
    int getDir(int index);
    int getEmptySlotsCnt();
    GraphicsItemParkingSlot *getEmptySlot();
    GraphicsItemParkingSlot *getSlot(int index);
public slots:
    void addCar(GraphicsItemCar* car);
    void addCar(GraphicsItemCar* car, int index);
private slots:
    void removeCar(GraphicsItemCar* car);
    void movementFinished(GraphicsItemCar* car);
private:
    int n, m;
    int col, row;
    int emptySlotsCnt;

    QPainterPath *p;

    void drawBackground(QPainter *painter, const QRectF &rect)override;
    std::vector<GraphicsItemParkingSlot*> parkingSlots;
};

#endif // CARPARKGRAPHICSVIEW_H
