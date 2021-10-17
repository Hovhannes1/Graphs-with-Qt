#include "canvas.h"
#include <QPointF>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    graphVertexList.push_back(new GraphVertex(QPointF(100, 100)));
    graphVertexList.push_back(new GraphVertex(QPointF(250, 350)));
    graphVertexList.push_back(new GraphVertex(QPointF(100, 200)));
    graphVertexList.push_back(new GraphVertex(QPointF(300, 200)));
    graphEdgeList.push_back(new GraphEdge(graphVertexList[0], graphVertexList[3]));
    graphEdgeList.push_back(new GraphEdge(graphVertexList[3], graphVertexList[0]));
    graphEdgeList.push_back(new GraphEdge(graphVertexList[0], graphVertexList[2]));
    graphEdgeList.push_back(new GraphEdge(graphVertexList[2], graphVertexList[1]));
    graphEdgeList.push_back(new GraphEdge(graphVertexList[2], graphVertexList[2]));
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for (auto &edge:graphEdgeList) {
        edge->draw(painter);
    }

    for (auto &vertex:graphVertexList) {
        vertex->draw(painter);
    }

}

void Canvas::mousePressEvent(QMouseEvent *event) {
    auto it = graphVertexList.begin();

    while (it!=graphVertexList.end() && !(*it)->isIn(event->pos())) {
        it++;
    }
    if(it != graphVertexList.end()) {
        if (selectedVertex != nullptr)  {
            selectedVertex->selected = false;
        }
        isMousePressed = true;
        selectedVertex=*it;
        selectedVertex->selected = true;
    } else {

        if (selectedVertex != nullptr) {
            selectedVertex->selected = false;
            this->update();
            selectedVertex = nullptr;
        }

        isMousePressed = false;
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *) {
    isMousePressed = false;
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (isMousePressed) {
        QPoint newPosstition = event->pos();
        selectedVertex->position = newPosstition;
        this->update();
    }
}

Canvas::~Canvas(){
    for (auto &e:graphVertexList){
        delete e;
    }

    graphVertexList.clear();
}
