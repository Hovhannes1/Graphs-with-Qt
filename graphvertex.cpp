#include "graphvertex.h"

int GraphVertex::next_id=0;
GraphVertex::GraphVertex(const QPointF &_position): id(next_id++), position(_position)
{

}

GraphVertex::GraphVertex(const int &_id, const QPointF &_position): id(_id), position(_position)
{

}

void drawInnerText(QPainter & painter, qreal x, qreal y, Qt::Alignment flags,
                   const QString & text)
{
    const qreal size = 32767.0;
    QPointF corner(x, y - size);
    if (flags & Qt::AlignHCenter) corner.rx() -= size/2.0;
    else if (flags & Qt::AlignRight) corner.rx() -= size;

    if (flags & Qt::AlignVCenter) corner.ry() += size/2.0003;
    else if (flags & Qt::AlignTop) corner.ry() += size;
    else flags |= Qt::AlignBottom;
    QRectF rect{corner.x(), corner.y(), size, size};
    painter.drawText(rect, flags, text);
}

void GraphVertex::draw(QPainter &painter)
{
    QBrush greenBrush(Qt::green,Qt::SolidPattern);
    QBrush yellowBrush(Qt::yellow,Qt::SolidPattern);
    QPen blackPen(Qt::black);
    QPen bluePen(Qt::blue);
    blackPen.setWidth(2);
    bluePen.setWidth(4);

    QFont serifFont("Times", 16, QFont::Normal);
    painter.setFont(serifFont);
    painter.save();

    if (this->selected) {
        painter.setBrush(yellowBrush);
        painter.setPen(bluePen);
    } else {
        painter.setBrush(greenBrush);
        painter.setPen(blackPen);
    }

    painter.drawEllipse(position.x() - radius, position.y() - radius, 2 * radius, 2 * radius);
    drawInnerText(painter, position.x(), position.y() + 2, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(this->id));
}

bool GraphVertex::isIn(const QPointF &pos) const
{
    if (std::pow(this->position.x()-pos.x(), 2) + std::pow(this->position.y()-pos.y(), 2) < radius*radius) {
        return true;
    }
    return false;
}


