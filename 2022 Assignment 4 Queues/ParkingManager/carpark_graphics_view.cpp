#include "carpark_graphics_view.h"
#include "parking_slot_graphics_item.h"

GraphicsViewCarPark::GraphicsViewCarPark(QWidget *parent): QGraphicsView(parent), p(nullptr), n(10), m(4), emptySlotsCnt(10)
{
    setRenderHint(QPainter::Antialiasing);
    setScene(new QGraphicsScene());
    scale(2.3, 2.3);
    init(n, m);
}

int GraphicsViewCarPark::getEmptySlotsCnt() {
    return emptySlotsCnt;
}

GraphicsItemParkingSlot *GraphicsViewCarPark::getEmptySlot() {
    for (auto e:parkingSlots) {
        if (e->isEmpty()) {
            return e;
        }
    }
    return nullptr;
}


GraphicsItemParkingSlot *GraphicsViewCarPark::getSlot(int index) {
    return parkingSlots[index - 1];
}


int GraphicsViewCarPark::getRow(int index) {
    return index ? (index - 1) / col + 1 : 0;
}

int GraphicsViewCarPark::getCol(int index) {
    return index ? (index - 1) % col + 1 : 0;
}

int GraphicsViewCarPark::getDir(int index) {
    return (getRow(index) - 1) / 2 % 2 ? -1 : 1;
}

/**
 * @brief Get the QPointF format position corresponding to the slot with index, 0 for entrance, n+1 for exit
 * @param index
 * @return QPointF format position
 */
QPointF GraphicsViewCarPark::getPos(int index) {
    if (index == 0)     return QPoint(0, 0);
    if (index == n + 1) return QPoint(getDir(n) > 0 ? (col + 1) * 10 : 0, getPathPos(n + 1).y() + 5 + 20);
    int &&i = getCol(index), &&j = getRow(index);
    return QPointF(i * 10, 10 + (j - 1) * 20 + (j) / 2 * 10);
}

/**
 * @brief Get the QPointF format position corresponding to the point on the
 * path in front of the slot with index, 0 for entrance, n+1 for exit
 * @param index
 * @return QPointF format position
 */
QPointF GraphicsViewCarPark::getPathPos(int index) {
    if (index == 0)     return QPoint(0, 20 + 5);
    if (index == n + 1) return QPoint(getDir(n) > 0 ? (col + 1) * 10 : 0, getPathPos(n).y());

    /*
      entrance
        *
        |[*][*][*][*][*]
        +-+--+--+--+--+-+
         [*][*][*][*][*]|
         [*][*][*][*][*]|
        +-+--+--+--+--+-+
        |[*][*][*][*][*]
        *
      exit
    */

    // The odd row faces south, and the even row faces north
    QPointF parkingSlotPos = getPos(index);
    return  QPointF(parkingSlotPos.x(), parkingSlotPos.y() + (getRow(index) % 2 ? 1 : -1) * (10 + 5) );
}

QPainterPath *GraphicsViewCarPark::generatePath(int src, int dst) {
    QPainterPath *path = new QPainterPath();
    if (src == dst) return path;
    bool reverse = src > dst;
    if (reverse) {
        std::swap(src, dst);
    }

    int cur = src;
    if (getRow(cur) % 2 == 0 && src != 0) cur -= col;

    QPointF curPos     = getPos(cur);

    path->moveTo(curPos);
    curPos = getPathPos(cur);
    path->lineTo(curPos);

    bool ok = false;
    while (dst == n + 1 || cur != dst && (cur == 0 || cur + col != dst)) {
        int dir = getDir(cur);

        while (getCol(cur) != (dir > 0 ? col : 1) && getPathPos(cur) != getPathPos(dst)) {
            curPos.rx() += dir * 10;
            cur += dir;
        }

        if (getPathPos(cur).y() == getPathPos(n).y() && dst == n + 1 || getPathPos(cur) == getPathPos(dst)) {
            path->lineTo(getPathPos(dst));
            path->lineTo(getPos(dst));
            ok = true;
            break;
        }

        curPos.rx() += dir * 10;
        path->lineTo(curPos);
        if (row - getRow(cur) >= 2) {
            curPos.ry() += 40 + 10;
            path->lineTo(curPos);
        } else {
            path->lineTo(getPathPos(n + 1));
            path->lineTo(getPos(n + 1));
            ok = true;
            break;
        }
        curPos.rx() -= dir * 10;
        path->lineTo(curPos);
        cur += 2*col;
    }
    if (!ok) {
        path->lineTo(getPos(dst));
    }
    if (reverse) *path = path->toReversed();
    return path;
}

void GraphicsViewCarPark::init(int n, int m) {
    qDebug() << "Init(" << n << ", " << m << ")";
    this->emptySlotsCnt = this->n = n;
    this->m = m;
    for (auto e: parkingSlots) {
        delete e;
    }
    parkingSlots.clear();

    col = 2 * ceil(sqrt(n * 0.5));
    row = (n + col - 1) / col;

    if (p != nullptr) delete(p);
    p = generatePath(0, n+1);

    scene()->clear();
    int cnt = 1, i = 0, j = 0;
    while (cnt <= n) {
        if (i == col) i = 0, j++;
        GraphicsItemParkingSlot* parkingSlot = new GraphicsItemParkingSlot(cnt);
        parkingSlots.push_back(parkingSlot);
        parkingSlot->setPos(getPos(cnt++));
        scene()->addItem(parkingSlot);
        i++;
    }
    scene()->update();
}

void GraphicsViewCarPark::drawBackground(QPainter *painter, const QRectF &rect) {
    painter->setPen(QColor(255, 100, 100));
    if (p != nullptr) painter->drawPath(*p);

    painter->drawPoint(getPos(0));
    painter->drawPoint(getPos(n + 1));
}

void GraphicsViewCarPark::addCar(GraphicsItemCar* car) {
    emptySlotsCnt--;
    car->updateInTime();
    connect(car, &GraphicsItemCar::removeCar,
            this, &GraphicsViewCarPark::removeCar);
    connect(car, &GraphicsItemCar::movementFinished,
            this, &GraphicsViewCarPark::movementFinished);
    car->setPos(0, 0);
    scene()->addItem(car);

    auto slot = getEmptySlot();
    slot->setCar(car);

    car->setPath(generatePath(0, slot->getIndex()));
}


void GraphicsViewCarPark::addCar(GraphicsItemCar* car, int index) {
    emptySlotsCnt--;
    car->updateInTime();
    connect(car, &GraphicsItemCar::removeCar,
            this, &GraphicsViewCarPark::removeCar);
    connect(car, &GraphicsItemCar::movementFinished,
            this, &GraphicsViewCarPark::movementFinished);
    car->setPos(0, 0);
    scene()->addItem(car);

    auto slot = parkingSlots[index- 1];
    slot->setCar(car);
    car->setPath(generatePath(0, slot->getIndex()));

}

void GraphicsViewCarPark::removeCar(GraphicsItemCar* car) {
    emptySlotsCnt++;
    for (auto e:parkingSlots) {
        if (e->getCar() == car) {
            e->setCar(nullptr);
            car->setPath(generatePath(e->getIndex(), n + 1));
            return;
        }
    }
}

void GraphicsViewCarPark::movementFinished(GraphicsItemCar* car) {
    if (car->pos() == getPos(n + 1)) {
        scene()->removeItem(car);
        emit outCar(car);
    }
}
