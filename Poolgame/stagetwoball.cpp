#include "stagetwoball.h"

void StageTwoBall::translate(QVector2D vec) {
    m_pos += vec;

    for (auto b : m_balls) {
        b->translate(vec);
    }

}

void StageTwoBall::render(QPainter &painter) {
    // use our colour
    painter.setBrush(m_brush);
    // circle centered
    painter.drawEllipse(m_pos.toPointF(), m_radius, m_radius);

    //draw the inner balls on top only if the user toggles it
    for (auto b : m_balls) {
        b->render(painter);
    }
}

std::vector<std::shared_ptr<Ball>> &StageTwoBall::getBalls() {
    return m_balls;
}


void StageTwoBall::addBall(std::shared_ptr<Ball> ball) {
    m_balls.push_back(std::move(ball));
}


double StageTwoBall::getStrength() const {
    return m_strength;
}

double StageTwoBall::getMass() const {
    double mass = m_mass;
    for (auto b : m_balls) {
        mass += b->getMass();
    }
    return mass;
}
