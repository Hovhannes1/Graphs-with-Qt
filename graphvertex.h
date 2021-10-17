#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H

#include <QMap>
#include <QtSvg/QSvgRenderer>
#include "graph.h"
#include <cmath>

class GraphVertex : public Graph
{
public:
    GraphVertex(const QPointF &_position);
    virtual void draw(QPainter &painter) override;
    virtual bool isIn(const QPointF &pos) const override;

    int getRadius() const {return radius;} ;
    const int id;
    static int next_id;

    bool selected = false;
    QPointF position;

private:
    int radius = 30;
};

#endif // GRAPHVERTEX_H
