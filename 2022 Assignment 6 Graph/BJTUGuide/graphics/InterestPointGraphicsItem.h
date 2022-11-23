//
// Created by AzurIce on 2022/11/24.
//

#ifndef BJTUGUIDE_INTERESTPOINTGRAPHICSITEM_H
#define BJTUGUIDE_INTERESTPOINTGRAPHICSITEM_H

#include <QRectF>
#include <QGraphicsItem>
#include <QPainter>
#include <atomic>

class InterestPointGraphicsItem : public QGraphicsItem {
public:
    InterestPointGraphicsItem(const QString &name, double x, double y) {
        m_name = name;
        setPos(x, y);
    }
    std::atomic<bool> selected = false;
    std::atomic<bool> checked = true;
    QString m_name;

    QRectF boundingRect() const override
    {
        qreal penWidth = 1;
        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                      20 + penWidth, 20 + penWidth);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override
    {
        painter->drawText(-4, -8, m_name);
//        painter->setPen(QPen(selected ? QColor(255, 0, 0) : QColor(100, 100, 100), 6));
//        painter->drawPoint(0, 0);
        painter->setBrush(QBrush(selected ? QColor(255, 0, 0) : checked ? QColor(100, 100, 100) : QColor(200, 200, 200)));
        painter->drawEllipse(0, 0, 10, 10);
//        painter->fillRect(-5, -5, 10, 10, QBrush(selected ? QColor(255, 0, 0) : QColor(100, 100, 100)));
    }
};


#endif //BJTUGUIDE_INTERESTPOINTGRAPHICSITEM_H
