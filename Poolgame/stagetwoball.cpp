#include "stagetwoball.h"

void StageTwoBall::translate(QVector2D vec) {
    m_pos += vec;

    for (auto b : m_balls) {
        b.get()->translate(vec);
    }

}

void StageTwoBall::render(QPainter &painter) {
    // use our colour
    painter.setBrush(m_brush);
    // circle centered
    painter.drawEllipse(m_pos.toPointF(), m_radius, m_radius);

    //draw the inner balls on top only if the user toggles it
    if (Ball::toggle) {
        for (auto b : m_balls) {
            b.get()->render(painter);
        }
    }
}


void StageTwoBall::addBalls(QJsonObject &ballData)
{

}
