#include "stagetwoball.h"

void StageTwoBall::translate(QVector2D vec) {
    m_pos += vec;

    for (auto b : m_balls) {
        //we update the position of our inner balls as well
        b->translate(vec);
    }

}

void StageTwoBall::render(QPainter &painter) {
    // use our colour
    painter.setBrush(m_brush);
    // circle centered
    painter.drawEllipse(m_pos.toPointF(), m_radius, m_radius);

    for (auto b : m_balls) {
        //we draw the inner balls
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
        //the effective mass of the ball includes the mass of the children balls
        mass += b->getMass();
    }
    return mass;
}
