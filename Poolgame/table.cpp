#include "table.h"

void StageOneTable::render(QPainter &painter) {
    // our table colour
    painter.setBrush(m_brush);
    // draw table
    painter.drawRect(this->getX(), this->getY(), this->getWidth(), this->getHeight());
}
