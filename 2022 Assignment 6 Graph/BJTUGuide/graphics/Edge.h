//
// Created by AzurIce on 2022/11/24.
//

#ifndef BJTUGUIDE_EDGE_H
#define BJTUGUIDE_EDGE_H

#include <QGraphicsItem>
#include "graphics/InterestPointGraphicsItem.h"

class Edge : public QGraphicsItem {
public:
    Edge(InterestPointGraphicsItem *source, InterestPointGraphicsItem *dest, double w, int next = 0)
            : source(source), dest(dest), w(w), next(next) {
        adjust();
    }

    InterestPointGraphicsItem *sourceNode() const { return source; }

    InterestPointGraphicsItem *destNode() const { return dest; }

    double w;
    int next;
    void adjust();

    bool m_selected = false;

protected:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    InterestPointGraphicsItem *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
};


#endif //BJTUGUIDE_EDGE_H
