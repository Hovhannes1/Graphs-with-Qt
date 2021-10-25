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

        qreal arrowSize = 20;

        QLineF line(this->dest->position, this->from->position);
        double angle = std::atan2(-line.dy(), line.dx());

        QPointF arrowP1 = arrowTipPoint + QPointF(sin(angle + M_PI / 4) * arrowSize,
                                              cos(angle + M_PI / 4) * arrowSize);
        QPointF arrowP2 = arrowTipPoint + QPointF(sin(angle + M_PI - M_PI / 4) * arrowSize,
                                              cos(angle + M_PI - M_PI / 4) * arrowSize);

        painter.drawLine(QLineF(arrowTipPoint, arrowP1));
        painter.drawLine(QLineF(arrowTipPoint, arrowP2));

        painter.strokePath(myPath, this->selected ? bluePen : redPen);
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

    qreal aX = 30 * (-1 * (dY / distance)) + mX;
    qreal aY = 30 * (dX / distance) + mY;

    arrowTipPoint = QPointF(aX, aY);
    curvePoint = QPointF(cX, cY);
}

bool GraphEdge::deleteEdge(GraphVertex *selectedVertex)
{
    if (this->from == selectedVertex || this->dest == selectedVertex) {
        return true;
    }
    return false;
}

bool GraphEdge::isIn(const QPointF &pos) const
{
    if (std::pow(this->arrowTipPoint.x()-pos.x(), 2) + std::pow(this->arrowTipPoint.y()-pos.y(), 2) < 20*20) {
        return true;
    }
    return false;
}
