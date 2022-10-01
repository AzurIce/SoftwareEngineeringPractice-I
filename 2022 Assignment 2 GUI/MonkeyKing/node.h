#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QGraphicsView>

class Edge;

class Node : public QGraphicsItem
{
public:
    Node(QGraphicsView *graphicsView, int id);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    bool advancePosition();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    QGraphicsView *graphicsView;
    int _id;
};

#endif // NODE_H
