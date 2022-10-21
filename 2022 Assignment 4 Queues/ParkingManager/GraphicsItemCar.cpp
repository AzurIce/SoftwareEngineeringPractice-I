#include "GraphicsItemCar.h"
#include <QGraphicsScene>
#include <cmath>
#include "Queue.h"
#define TICK_RATE 60
#define MAX_TICK_STAY 20

#define SPEED 1.3


template<>
QString Queue<GraphicsItemCar *>::toString() {
    QString s = "[";
    for (int i = _front; i != _rear; i = indexAdd(i, 1)) {
        s.append(_queue[i]->getLicense());
        if (indexAdd(i, 1) != _rear) s.append(", ");
    }
    s.append("]");
    return s;
}

QString GraphicsItemCar::getLicense() {
    return license;
}

time_t GraphicsItemCar::getTimeIn() {
    return time_in;
}
time_t GraphicsItemCar::getTimeOut() {
    return time_out;
}


QString GraphicsItemCar::getCTimeIn() {
    return ctime_in;
}
QString GraphicsItemCar::getCTimeOut() {
    return ctime_out;
}


void GraphicsItemCar::updateInTime() {
    time(&time_in);
    ctime_in = QString(ctime(&time_in));
}

void GraphicsItemCar::updateOutTime() {
    time(&time_out);
    ctime_out = QString(ctime(&time_out));
}

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle > 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}

GraphicsItemCar::GraphicsItemCar(QString license, int index):
    path(nullptr), pathProgress(0), tick_stay((rand() % MAX_TICK_STAY  + 1) * TICK_RATE), license(license), index(index) {}

QRectF GraphicsItemCar::boundingRect() const {
    return QRectF(-5, -10, 10, 20);
}

void GraphicsItemCar::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
//    painter->rotate(angle);
    painter->setBrush(QColor(100, 100, 100));
    painter->drawRect(-3, -6, 6, 10);
}

int GraphicsItemCar::getIndex() {
    return index;
}

double GraphicsItemCar::cauculateCost() {
    /*
     * 15分钟为1个计时单位，满1个计时单位后方可收取停车费，不足1个计时单位的不收取费用。收费标准为1.5元/15分钟，不分白天晚上。
     * 5s = 15min
     * 5s 后收费，不足1s不收费。
     * 1.5元/5s
     */
    long long seconds = time_out - time_in;
    if (seconds < 5) return 0;
    return 1.5 * seconds / 5;
}

void GraphicsItemCar::setPath(QPainterPath* path) {
    if (this->path != nullptr) delete(this->path);
    this->path = path;
    pathProgress = 0;
    setPos(path->pointAtPercent(0));
}

void GraphicsItemCar::advance(int step) {
    if (!step) return;
    if (path != nullptr) {
        double step = SPEED / path->length();
        auto p1 = pos(), p2 = path->pointAtPercent(pathProgress + step > 1 ? 1 : pathProgress + step);

        auto pDir = path->pointAtPercent(pathProgress + 20 * step > 1 ? 1 : pathProgress + step);

        QLineF line(p1, pDir);
        pathProgress += step;
//        qDebug() << "p2: " << p2;
        angle = std::atan2(-line.dy(), line.dx());
//        qDebug() << "Delta y: " << line.dy() << "Delta x: " << line.dx();
//        qDebug() << "Angle: " << angle;
        angle = normalizeAngle((M_PI - angle) + M_PI / 2);
//        if (angle >= 0 && angle < M_PI / 2) {
//            // Rotate right
//            angle += 0.2;
//        } else if (angle <= 2 * M_PI && angle > (2 * M_PI - M_PI / 2)) {
//            // Rotate left
//            angle -= 0.2;
//        }
//        qreal dx = sin(angle) * 10;
//        setRotation(rotation() + dx);

        setRotation(angle * 360 / 2 / M_PI);
        setPos(p2);
        if (pathProgress >= 1) {
            path = nullptr;
            emit movementFinished(this);
        }
    } else {
        if (!tick_stay) {
            emit removeCar(this);
        }
        tick_stay--;
//        qDebug() << tick_stay;
    }
}
