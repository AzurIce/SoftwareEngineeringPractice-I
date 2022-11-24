//
// Created by AzurIce on 2022/11/24.
//

#include "Edge.h"

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}


QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = penWidth / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}


void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    if (m_selected) {
        painter->setPen(QPen(QColor(110, 110, 220), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    } else {
        painter->setPen(QPen(QColor(160, 160, 160), 1, Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
    }
    painter->drawLine(line);

    if (m_selected) {
        painter->setPen(QPen(QColor(110, 110, 220), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    } else {
        painter->setPen(QPen(QColor(110, 110, 110), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    painter->drawText((sourcePoint + destPoint) / 2, QString::number(w));
}
