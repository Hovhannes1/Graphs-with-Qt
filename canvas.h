#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QMainWindow>
#include <QPointF>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QString>

#include "graphedge.h"
#include "graphvertex.h"

class MainWindow;


class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event) override;

    void setMainWindow(MainWindow* w) {_mainWindow = w;};

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    GraphVertex *selectedVertex = nullptr;
    GraphEdge *selectedEdge = nullptr;

    bool isMousePressed = false;
    bool edgeCreationStarted = false;

    int getEdgeListLength() {return graphEdgeList.length();}
    int getVertexListLength() {return graphVertexList.length();}

    QList<GraphVertex*> getVertexList() {return graphVertexList;};
    QList<GraphEdge*> getEdgeList() {return graphEdgeList;};

    void createVertex();
    void createEdge(GraphVertex *secondVertex);

    void deleteVertex();
    void deleteEdge();

    void loadJSON(const QByteArray &data);

    void detAdjacencyMatrix();

    ~Canvas();

private:
    QList<GraphEdge*> graphEdgeList;
    QList<GraphVertex*> graphVertexList;

    MainWindow* _mainWindow = nullptr;
};

#endif // CANVAS_H
