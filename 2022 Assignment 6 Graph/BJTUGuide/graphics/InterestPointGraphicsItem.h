//
// Created by AzurIce on 2022/11/24.
//

#ifndef BJTUGUIDE_INTERESTPOINTGRAPHICSITEM_H
#define BJTUGUIDE_INTERESTPOINTGRAPHICSITEM_H

#include <QRectF>
#include <QGraphicsItem>
#include <QPainter>
#include <atomic>
#include <utility>
#include "utils/GeoUtils.h"
#include "models/InterestPointData.h"

class InterestPointGraphicsItem : public QGraphicsItem {
public:
    explicit InterestPointGraphicsItem(const InterestPointData &data) : data(data) {
        auto [x, y] = GeoUtils::getCoord(data.lat, data.lng);
        setPos(x, y);
    }

    InterestPointData data;

    std::atomic<bool> m_passed = false;

    [[nodiscard]] QRectF boundingRect() const override {
        qreal penWidth = 1;
        return {-10 - penWidth / 2, -10 - penWidth / 2, 20 + penWidth, 20 + penWidth};
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        painter->drawText(-4, m_passed ? -16 : -8, data.name);
        if (data.selected) {
            painter->setPen(QPen(QColor(255, 0, 0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        } else {
            painter->setPen(QPen(QColor(160, 160, 160), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        painter->setBrush(QBrush(m_passed ? QColor(110, 110, 220) : QColor(160, 160, 160)));
        painter->drawEllipse(data.checked ? -10 : -5, data.checked ? -10 : -5, data.checked ? 20 : 10, data.checked ? 20 : 10);
    }
};


#endif //BJTUGUIDE_INTERESTPOINTGRAPHICSITEM_H
