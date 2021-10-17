#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>

#include "graphedge.h"
#include "graphvertex.h"

class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    GraphVertex *selectedVertex = nullptr;
    bool isMousePressed = false;

    int getEdgeListLength() {return graphEdgeList.length();}
    int getVertexListLength() {return graphVertexList.length();}

    ~Canvas();

private:
    QList<GraphEdge*> graphEdgeList;
    QList<GraphVertex*> graphVertexList;
};

#endif // CANVAS_H
