#include "stagetwopocket.h"

void StageTwoPocket::render(QPainter& painter) {
    painter.save();
    // set color to black
    painter.setBrush(QBrush(QColor("black")));
    // pocket centered
    painter.drawEllipse(m_pos.toPointF(), m_radius, m_radius);
    painter.restore();
}
