#include "stagetwopocket.h"

StageTwoPocket::StageTwoPocket(QVector2D pos, double radius):
    Pocket(pos, radius)
{

}

void StageTwoPocket::render(QPainter& painter) {
    // set color to black
    painter.setBrush(QBrush(QColor("black")));
    // pocket centered
    painter.drawEllipse(m_pos.toPointF(), m_radius, m_radius);
}
