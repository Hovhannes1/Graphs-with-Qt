#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QPointF>
#include <QWidget>

class Graph
{
public:
    Graph();
    virtual ~Graph(){};
    virtual void draw(QPainter &painter)=0;
    virtual bool isIn(const QPointF &pos) const=0;
private:

};

#endif // GRAPH_H
