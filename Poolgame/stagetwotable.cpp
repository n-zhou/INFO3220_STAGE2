#include "stagetwotable.h"

void StageTwoTable::render(QPainter &painter)
{
    // our table colour
    painter.setBrush(m_brush);
    // draw table
    painter.drawRect(this->getX(), this->getY(), this->getWidth(), this->getHeight());

    //draw our pockets
    for (auto p : *m_pockets) {
        p.get()->render(painter);
    }
}
