#include "pocket.h"

Pocket::Pocket(QVector2D pos, double radius)
    : m_pos(pos), m_radius(radius)
{

}

Pocket::~Pocket()
{

}

void Pocket::render(QPainter& painter)
{
    // set color to black
    painter.setBrush(QBrush(QColor("black")));
    // pocket centered
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
