#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include "graph.h"
#include "graphvertex.h"


class GraphEdge : public Graph
{
public:
    GraphEdge(GraphVertex* &_from, GraphVertex* &_dest);
    virtual void draw(QPainter &painter) override;
    virtual bool isIn(const QPointF &pos) const override;

    void calculateCurvePoint();

    QPointF curvePoint;

    bool selected = false;

private:
    GraphVertex *from;
    GraphVertex *dest;
};

#endif // GRAPHEDGE_H
