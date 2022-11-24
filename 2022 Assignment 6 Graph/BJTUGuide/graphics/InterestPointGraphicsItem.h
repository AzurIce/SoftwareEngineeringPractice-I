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

class InterestPointGraphicsItem : public QGraphicsItem {
public:
    InterestPointGraphicsItem(int id, QString name, double lat, double lng,
                              bool selected = false, bool checked = true):
                              m_id(id), m_name(std::move(name)), m_selected(selected), m_checked(checked) {
        auto [x, y] = GeoUtils::getCoord(lat, lng);
        setPos(x, y);
    }

    int m_id;
    std::atomic<bool> m_selected = false;
    std::atomic<bool> m_checked = true;
    std::atomic<bool> m_passed = false;
    QString m_name;

    QRectF boundingRect() const override {
        qreal penWidth = 1;
        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2, 20 + penWidth, 20 + penWidth);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        painter->drawText(-4, m_passed ? -16 : -8, m_name);
        if (m_selected) {
            painter->setPen(QPen(QColor(255, 0, 0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        } else {
            painter->setPen(QPen(QColor(160, 160, 160), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        painter->setBrush(QBrush(m_passed ? QColor(110, 110, 220) : QColor(160, 160, 160)));
        painter->drawEllipse(m_checked ? -10 : -5, m_checked ? -10 : -5, m_checked ? 20 : 10, m_checked ? 20 : 10);
    }
};


#endif //BJTUGUIDE_INTERESTPOINTGRAPHICSITEM_H
