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
    bool deleteEdge(GraphVertex *selectedVertex);

    GraphVertex *getFromVertex() {return from;}
    GraphVertex *getDestVertex() {return dest;}

    bool selected = false;

private:
    GraphVertex *from;
    GraphVertex *dest;

    QPointF curvePoint;
    QPointF arrowTipPoint;
};

#endif // GRAPHEDGE_H
