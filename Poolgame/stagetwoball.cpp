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

std::vector<std::shared_ptr<Ball>>* StageTwoBall::getBalls()
{
    return &m_balls;
}


void StageTwoBall::addBalls(QJsonArray &ballArray)
{
    for (int i = 0; i < ballArray.size(); ++i) {
        //set attributes to default
        std::string colour = this->getColour().name().toStdString();
        double mass = Default::Ball::mass;
        double strength = Default::Ball::strength;
        double radius = Default::Ball::radius;
        QVector2D pos(0, 0);
        QVector2D vel(0, 0);

        QJsonObject ballData = ballArray[i].toObject();
        //check for ball colour
        if (ballData.contains("colour")) {
            colour = ballData["colour"].toString().toStdString();
        } else {
            std::cerr << "missing ball colour" << std::endl;
        }

        //check for ball mass
        if (ballData.contains("mass")) {
            mass = ballData["mass"].toDouble();
        } else {
            std::cerr << "missing ball mass" << std::endl;
        }

        //check for ball strength
        if (ballData.contains("strength")) {
            strength = ballData["strength"].toDouble();
        } else {
            std::cerr << "missing ball strength" << std::endl;
        }

        //check for ball radius
        if (ballData.contains("radius")) {
            radius = ballData["radius"].toDouble();
        } else {
            std::cerr << "ball radius missing" << std::endl;
        }

        //check the ball position
        if (ballData.contains("position")) {
            QJsonObject ballPosition = ballData["position"].toObject();

            //check the ball's x position
            if (ballPosition.contains("x")) {
                pos.setX(ballPosition["x"].toDouble());
                std::cerr << "ballxPos " << pos.x() << std::endl;
            } else {
                std::cerr << "missing ball x position" << std::endl;
            }

            //check the ball's y position
            if (ballPosition.contains("y")) {
                pos.setY(ballPosition["y"].toDouble());
            } else {
                std::cerr << "missing ball y position" << std::endl;
            }
        } else {
            std::cerr << "missing both ball position" << std::endl;
        }

        //check the velocity
        if (ballData.contains("velocity")) {
            QJsonObject ballVelocity = ballData["velocity"].toObject();

            //check the ball's x velocity
            if (ballVelocity.contains("x")) {
                vel.setX(ballVelocity["x"].toDouble());
            } else {
                std::cerr << "missing ball x velocity" << std::endl;
            }

            //check the ball's y velocity
            if (ballVelocity.contains("y")) {
                vel.setY(ballVelocity["y"].toDouble());
            } else {
                std::cerr << "missing ball y velocity" << std::endl;
            }
        } else {
            std::cerr << "ball velocity not provided" << std::endl;
        }

        //set the position relative to the parent
        pos.setX(this->m_pos.x() + pos.x());
        pos.setY(this->m_pos.y() + pos.y());

        //check the inner ball is fully contained in the parent ball
        if ((this->getPosition().distanceToPoint(pos) + radius) > this->m_radius) {
            continue;
        }

        StageTwoBall *temp = new StageTwoBall(QColor(colour.c_str()), pos, vel, mass, radius, strength);
        QJsonArray ballArray1= ballData["balls"].toArray();
        temp->addBalls(ballArray1);
        this->m_balls.push_back(std::shared_ptr<Ball>(temp));
    }
}


double StageTwoBall::getStrength() const
{
    return m_strength;
}

double StageTwoBall::getMass()
{
    double mass = m_mass;
    for (auto b : m_balls) {
        mass += b->getMass();
    }
    return mass;
}
