#include "canvas.h"

#include "mainwindow.h"
#include <iostream>

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

void Canvas::detAdjacencyMatrix() {
    int max = graphVertexList.length();
    int adjacencyMatrix[max][max];
    memset(adjacencyMatrix, 0, max*max*sizeof(int));

    for (auto &edge:graphEdgeList) {
        adjacencyMatrix[edge->getFromVertex()->id][edge->getDestVertex()->id] = 1;
    }
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    //Edge clicking part
    auto itEdge = graphEdgeList.begin();
    while (itEdge!=graphEdgeList.end() && !(*itEdge)->isIn(event->pos())) {
        itEdge++;
    }

    // Vertex clicking part
    auto it = graphVertexList.begin();
    while (it!=graphVertexList.end() && !(*it)->isIn(event->pos())) {
        it++;
    }

    //Edge clicked check
    if(itEdge != graphEdgeList.end()) {
        if (selectedEdge != nullptr)  {
            selectedEdge->selected = false;
        }
        isMousePressed = true;
        selectedEdge=*itEdge;
        selectedEdge->selected = true;
        _mainWindow->startEdgeDeletion();

        if (selectedVertex != nullptr) {
            selectedVertex->selected = false;
            _mainWindow->cancelVertexDeletion();
            selectedVertex = nullptr;
        }
    }
    // Vertex clicked check
    else if(it != graphVertexList.end()) {
        if (selectedVertex != nullptr)  {
            selectedVertex->selected = false;
        }
        isMousePressed = true;
        if (edgeCreationStarted) {
            createEdge(*it);
        }
        selectedVertex=*it;
        selectedVertex->selected = true;
        _mainWindow->startVertexDeletion();

        if (selectedEdge != nullptr) {
            selectedEdge->selected = false;
            _mainWindow->cancelEdgeDeletion();
            selectedEdge = nullptr;
        }
    } else {

        if (selectedVertex != nullptr) {
            selectedVertex->selected = false;
            _mainWindow->cancelVertexDeletion();
            selectedVertex = nullptr;
        }

        if (selectedEdge != nullptr) {
            selectedEdge->selected = false;
            _mainWindow->cancelEdgeDeletion();
            selectedEdge = nullptr;
        }

        isMousePressed = false;
    }
    this->update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *) {
    isMousePressed = false;
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (isMousePressed && selectedVertex != nullptr) {
        QPoint newPosstition = event->pos();
        selectedVertex->position = newPosstition;
        this->update();
    }
}

void Canvas::createVertex()
{
    if (graphVertexList.isEmpty()) {
        graphVertexList.push_back(new GraphVertex(0, QPointF(300, 300)));
    } else {
        graphVertexList.push_back(new GraphVertex(graphVertexList.last()->id + 1, QPointF(500, 500)));
    }

    _mainWindow->updateStatusbar();
}

void Canvas::createEdge(GraphVertex *secondVertex)
{
    if (selectedVertex != nullptr) {
        graphEdgeList.push_back(new GraphEdge(selectedVertex, secondVertex));
        _mainWindow->cancelEdgeCreation();
        _mainWindow->updateStatusbar();
    }
}

void Canvas::deleteVertex()
{
    for (auto &&edge: graphEdgeList) {
        if(edge->deleteEdge(selectedVertex)) {
            graphEdgeList.removeOne(edge);
        }
    }
    graphVertexList.removeOne(selectedVertex);
    selectedVertex = nullptr;
    this->update();
}

void Canvas::deleteEdge()
{
    graphEdgeList.removeOne(selectedEdge);
    selectedEdge = nullptr;
    this->update();
}

void Canvas::loadJSON(const QByteArray &data) {
    if (!data.isEmpty()) {
        graphVertexList.clear();
        graphEdgeList.clear();

        QString JSON = data;

        QJsonDocument doc = QJsonDocument::fromJson(JSON.toUtf8());
        QJsonArray JSONvertices = doc["vertices"].toArray();
        for (auto &&v:JSONvertices) {
            QJsonObject vector = v.toObject();
            int x,y;
            auto strPosition = vector["position"].toString().split(',');
            x = strPosition[0].toInt();
            y = strPosition[1].toInt();
            GraphVertex *newVertex = new GraphVertex(vector["id"].toInt(),QPointF(x,y));
            graphVertexList.push_back(newVertex);
        }

        QJsonArray JSONedges = doc["edges"].toArray();
        for (auto &&v:JSONedges) {
            QJsonObject vector = v.toObject();
//            qDebug() << vector["from"].toInt() << "," << vector["dest"].toInt();
            unsigned int val = vector["from"].toInt();
            auto from = std::find_if(graphVertexList.begin(),graphVertexList.end(),[val](const GraphVertex *gv) {
                return gv->id == int(val);
            });
            val = vector["dest"].toInt();
            auto dest = std::find_if(graphVertexList.begin(),graphVertexList.end(),[val](const GraphVertex *gv) {
                return gv->id == int(val);
            });
            GraphEdge *newEdge;

            newEdge = new GraphEdge(*from,*dest);

            graphEdgeList.push_back(newEdge);
        }
        _mainWindow->updateStatusbar();
    }
}

Canvas::~Canvas(){
    delete selectedVertex;
    delete selectedEdge;

    for (auto &v:graphVertexList){
        delete v;
    }

    for (auto &e:graphEdgeList){
        delete e;
    }

    graphVertexList.clear();
    graphEdgeList.clear();

    delete _mainWindow;
}
