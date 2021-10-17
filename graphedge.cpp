#include "graphedge.h"

GraphEdge::GraphEdge(GraphVertex* &_from, GraphVertex* &_dest):
      from(_from), dest(_dest)
{

}

void GraphEdge::draw(QPainter &painter)
{
    QPen redPen(Qt::red);
    QPen bluePen(Qt::blue);
    redPen.setWidth(6);
    bluePen.setWidth(8);
    painter.save();

    if (this->selected) {
        painter.setPen(bluePen);
    } else {
        painter.setPen(redPen);
    }
    QPainterPath myPath;

    calculateCurvePoint();

    if (this->from->position == this->dest->position) {
        QBrush whiteBrush(Qt::transparent,Qt::SolidPattern);
        painter.setBrush(whiteBrush);
        painter.drawEllipse(this->from->position.x() - 60, this->from->position.y() - 30, 60, 60);
    } else {
        myPath.moveTo(this->from->position);
        myPath.quadTo(curvePoint, this->dest->position);
//        painter.drawLine(curvePoint - QPointF(10, 10), curvePoint);
        painter.strokePath(myPath, redPen);
    }
}

void GraphEdge::calculateCurvePoint()
{
    // We first calculate the distance covered by our edge
    qreal dX = dest->position.x() - from->position.x();
    qreal dY = dest->position.y() - from->position.y();
    qreal distance = sqrt(pow(dX, 2) + pow(dY, 2));
    // Then we create a straight line from our from point to our dest point and shorten its length
    QLineF newLine = QLineF(from->position, dest->position);
    newLine.setLength(newLine.length() - 18);
    // Then we calculate the coordinates of our midpoint
    qreal mX = (from->position.x() + newLine.p2().x()) / 2;
    qreal mY = (from->position.y() + newLine.p2().y()) / 2;
    // We use the 2*radius of Vertex as a scaling factor
    // to determine the 'height' of the curving point
    qreal cX = 60 * (-1 * (dY / distance)) + mX;
    qreal cY = 60 * (dX / distance) + mY;
    curvePoint = QPointF(cX, cY);
}

bool GraphEdge::isIn(const QPointF &pos) const
{
    return false;
}
