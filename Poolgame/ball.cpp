#include "ball.h"
void StageOneBall::translate(QVector2D vec) {
    m_pos += vec;
}

void StageOneBall::render(QPainter &painter) {
    // use our colour
    painter.setBrush(m_brush);
    // circle centered
    painter.drawEllipse(m_pos.toPointF(), m_radius, m_radius);
}
