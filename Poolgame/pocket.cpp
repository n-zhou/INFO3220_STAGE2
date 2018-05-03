#include "pocket.h"

Pocket::Pocket(QVector2D pos, double radius)
    : m_pos(pos), m_radius(radius)
{

}

void Pocket::render(QPainter& painter)
{
    // use our colour
    painter.setBrush(QBrush(QColor("black")));
    // circle centered
    painter.drawEllipse(m_pos.toPointF(), m_radius, m_radius);
}

QVector2D Pocket::getPos()
{
    return m_pos;
}

double Pocket::getRadius()
{
    return m_radius;
}
