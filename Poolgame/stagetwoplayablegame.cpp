#include "stagetwoplayablegame.h"

StageTwoPlayableGame::StageTwoPlayableGame(Table *table, std::vector<std::shared_ptr<Ball>> *balls)
    : AbstractPlayableGame(), m_table(table), m_balls(balls), m_clicked(false)
{
    //set the white ball
    for (auto b : *m_balls) {
        if (b.get()->getColour() == QColor("white")) {
            whiteBall = b;
            break;
        }
    }

    //remove out of bounds ball
    for (auto i = m_balls->begin(); i != m_balls->end(); ++i) {
        std::shared_ptr<Ball> b = *i;
        if (isCollision(m_table, b.get())) {
            m_balls->erase(i--);
        }
    }
}

void StageTwoPlayableGame::rightClick(QMouseEvent *e)
{
    //toggles the visibility of the inner balls on
    Ball::toggle = true;
}

void StageTwoPlayableGame::rightClickRelease(QMouseEvent *e)
{
    //toggles the visiblity of the inner balls off
    Ball::toggle = false;
}

void StageTwoPlayableGame::leftClick(QMouseEvent *e)
{
    if (whiteBall.expired()) {
        return;
    }
    QVector2D velocity = whiteBall.lock()->getVelocity();
    //we allow an epsilon on 2 when deciding whether the white ball is stationary
    if (std::fabs(velocity.x()) > 2 || std::fabs(velocity.y()) > 2) {
        std::cout << "You can only hit the cue when it's not moving!" << std::endl;
        return;
    }
    mousePos.setX(e->x());
    mousePos.setY(e->y());
    if (whiteBall.lock()->getPosition().distanceToPoint(mousePos) <= whiteBall.lock()->getRadius()) {
        m_clicked = true;
    }
}

void StageTwoPlayableGame::leftClickRelease(QMouseEvent *e)
{
    if (m_clicked) {
        mousePos.setX(e->x());
        mousePos.setY(e->y());
        hitTheWhiteBall();
        m_clicked = false;
    }
}

void StageTwoPlayableGame::mouseDrag(QMouseEvent *e)
{
    if (m_clicked) {
        mousePos.setX(e->x());
        mousePos.setY(e->y());
    }
}

void StageTwoPlayableGame::render(QPainter &painter)
{
    m_table->render(painter);
    for (std::shared_ptr<Ball> b : *m_balls) {
        b.get()->render(painter);
    }

    //draws the line while the left mouse button is clicked
    if (m_clicked && !whiteBall.expired()) {
        //thickness of the line is set to illustrate power of shot
        painter.save();
        double distance = whiteBall.lock()->getPosition().distanceToPoint(mousePos);
        int thickness = std::fmin(distance/60, 10);
        painter.setPen(QPen(Qt::black, thickness, Qt::DotLine, Qt::RoundCap));
        painter.drawLine(whiteBall.lock()->getPosition().toPointF(), mousePos.toPointF());
        painter.restore();
    }
}

int StageTwoPlayableGame::getMinimumHeight() const
{
    return m_table->getHeight();
}

int StageTwoPlayableGame::getMinimumWidth() const
{
    return m_table->getWidth();
}

void StageTwoPlayableGame::animate(double dt){

    //remove balls that are encompassed in pockets
    for (int i = 0; i < m_balls->size(); ++i) {
        std::shared_ptr<Ball> ballA = m_balls->at(i);
        for (auto pocket : *(m_table->getPockets())) {
            if (ballA.get()->getPosition().distanceToPoint(pocket.get()->getPos()) + ballA.get()->getRadius() <= pocket.get()->getRadius()) {
                m_balls->erase(m_balls->begin() + i--);
                break;
            }
        }
    }

    std::vector<std::shared_ptr<Ball>> oddChildren;

    for (int i = 0; i < m_balls->size(); ++i) {
        std::shared_ptr<Ball> ballA = m_balls->at(i);
        for (int j = i + 1; j < m_balls->size(); ++j) {
            std::shared_ptr<Ball> ballB = m_balls->at(j);
            if (isCollision(ballA.get(), ballB.get())) {
                if (isBreakable(ballA.get(), ballB.get()) && isBreakable(ballB.get(), ballB.get())) {
                    std::vector<std::shared_ptr<Ball>> *copy1 = breakBall(ballA.get(), ballB.get());
                    std::vector<std::shared_ptr<Ball>> *copy2 = breakBall(ballB.get(), ballA.get());
                    oddChildren.insert(oddChildren.end(), copy1->begin(), copy1->end());
                    oddChildren.insert(oddChildren.end(), copy2->begin(), copy2->end());
                    m_balls->erase(m_balls->begin() + j);
                    m_balls->erase(m_balls->begin() + i--);
                    break;
                } else if (isBreakable(ballA.get(), ballB.get())) {
                    std::vector<std::shared_ptr<Ball>> *copy = breakBall(ballA.get(), ballB.get());
                    oddChildren.insert(oddChildren.end(), copy->begin(), copy->end());
                    m_balls->erase(m_balls->begin() + i--);
                    break;
                } else if (isBreakable(ballB.get(), ballA.get())) {
                    std::vector<std::shared_ptr<Ball>> *copy = breakBall(ballB.get(), ballA.get());
                    oddChildren.insert(oddChildren.end(), copy->begin(), copy->end());
                    m_balls->erase(m_balls->begin() + j--);
                }
            }

        }
    }

    m_balls->insert(m_balls->end(), oddChildren.begin(), oddChildren.end());

    for (auto it = m_balls->begin(); it != m_balls->end(); ++it) {
        std::shared_ptr<Ball> ballA = *it;
        // correct ball velocity if colliding with table
        resolveCollision(m_table, ballA.get());
        // check collision with all later balls
        for (auto nestedIt = it + 1; nestedIt != m_balls->end(); ++nestedIt) {
            std::shared_ptr<Ball> ballB = *nestedIt;
            if (isCollision(ballA.get(), ballB.get())) {
                 resolveCollision(ballA.get(), ballB.get());
            }
        }

        // move ball due to speed
        ballA->translate(ballA->getVelocity() * dt);

        //set the velocity of the ball to 0 if it's close enough to 0
        if (std::fabs(ballA->getVelocity().x()) < 3 && std::fabs(ballA->getVelocity().y()) < 3) {
            ballA->multiplyVelocity(QVector2D(0, 0));
            continue;
        }
        // apply frictionz
        ballA->changeVelocity(-ballA->getVelocity() * m_table->getFriction() * dt);


    }

}

std::vector<std::shared_ptr<Ball>>* StageTwoPlayableGame::breakBall(Ball *ballA, Ball *ballB)
{
    // if not colliding (distance is larger than radii)
    //Properties of two colliding balls,
     //ball A
     QVector2D posA = ballA->getPosition();
     QVector2D velA = ballA->getVelocity();
     float massA = ballA->getMass();
     //and ball B
     QVector2D posB = ballB->getPosition();
     QVector2D velB = ballB->getVelocity();
     float massB = ballB->getMass();

     //calculate their mass ratio
     float mR = massB / massA;

     //calculate the axis of collision
     QVector2D collisionVector = posB - posA;
     collisionVector.normalize();

    //the proportion of each balls velocity along the axis of collision
     double vA = QVector2D::dotProduct(collisionVector, velA);
     double vB = QVector2D::dotProduct(collisionVector, velB);
     //the balls are moving away from each other so do nothing
     if (vA <= 0 && vB >= 0) {
        //return;
     }

     //The velocity of each ball after a collision can be found by solving the quadratic equation
     //given by equating momentum and energy before and after the collision and finding the velocities
     //that satisfy this
     //-(mR+1)x^2 2*(mR*vB+vA)x -((mR-1)*vB^2+2*vA*vB)=0
     //first we find the discriminant
     double a = -(mR + 1);
     double b = 2 * (mR * vB + vA);
     double c = -((mR - 1) * vB * vB + 2 * vA * vB);
     double discriminant = sqrt(b * b - 4 * a * c);
     double root = (-b + discriminant)/(2 * a);
     //only one of the roots is the solution, the other pertains to the current velocities
     if (root - vB < 0.01) {
        root = (-b - discriminant)/(2 * a);
     }


    //The resulting changes in velocity for ball A and B
    QVector2D deltaVA = mR * (vB - root) * collisionVector;
    QVector2D deltaVB = (root - vB) * collisionVector;

    StageTwoBall *bA = dynamic_cast<StageTwoBall*>(ballA);
    std::vector<std::shared_ptr<Ball>> *children = bA->getBalls();
    float ballMass = bA->getMass();
    float ballStrength = bA->getStrength();
    float ballRadius = bA->getRadius();
    QVector2D preCollisionVelocity = ballA->getVelocity();
    QVector2D deltaV = deltaVA;
    float energyOfCollision = ballMass*deltaV.lengthSquared();
    float energyPerBall = energyOfCollision/children->size();
    QVector2D pointOfCollision((-deltaV.normalized())*ballRadius);

    //for each component ball
    for (int i = 0; i < children->size(); ++i) {
        std::shared_ptr<Ball> child = children->at(i);
        QVector2D componentBallVelocity = preCollisionVelocity + sqrt(energyPerBall/child.get()->getMass())*(child.get()->getPosition()-pointOfCollision).normalized();
        child.get()->multiplyVelocity(QVector2D(0, 0));
        child.get()->changeVelocity(componentBallVelocity);
    }
    return children;
}

bool StageTwoPlayableGame::isCollision(const Table *table, const Ball *b) const
{
    QVector2D bPos = b->getPosition();

    //left side
    if (bPos.x() + b->getRadius() > table->getWidth()) {
        return true;
    } else if (bPos.x() - b->getRadius() < 0) {
        return false;
    } else if (bPos.y() + b->getRadius() > table->getHeight()) {
        return true;
    } else if (bPos.y() - b->getRadius() < 0) {
        return true;
    }

    return false;
}

void StageTwoPlayableGame::resolveCollision(Table *table, Ball *ball)
{
    QVector2D bPos = ball->getPosition();

    // resulting multiplicity of direction. If a component is set to -1, it
    // will flip the velocity's corresponding component
    QVector2D vChange(1,1);

    // ball is beyond left side of table's bounds
    if (bPos.x() - ball->getRadius() <= table->getX()) {
        // flip velocity if wrong dir
        if (ball->getVelocity().x() <= 0) vChange.setX(-1);
    // ball is beyond right side of table's bounds
    } else if (bPos.x() + ball->getRadius() >= table->getX() + table->getWidth()) {
        // flip velocity if wrong dir
        if (ball->getVelocity().x() >= 0) vChange.setX(-1);
    }
    // ball is above top of the table's bounds
    if (bPos.y() - ball->getRadius() <= table->getY()) {
        // flip iff we're travelling in the wrong dir
        if (ball->getVelocity().y() <= 0) vChange.setY(-1);
    // ball is beyond bottom of table's bounds
    } else if (bPos.y() + ball->getRadius() >= table->getY() + table->getHeight()) {
        // if we're moving down (we want to let the ball bounce up if its heading back)
        if (ball->getVelocity().y() >= 0) vChange.setY(-1);
    }

    ball->multiplyVelocity(vChange);
}

void StageTwoPlayableGame::resolveCollision(Ball *ballA, Ball *ballB)
{
    // if not colliding (distance is larger than radii)
    //Properties of two colliding balls,
     //ball A
     QVector2D posA = ballA->getPosition();
     QVector2D velA = ballA->getVelocity();
     float massA = ballA->getMass();
     //and ball B
     QVector2D posB = ballB->getPosition();
     QVector2D velB = ballB->getVelocity();
     float massB = ballB->getMass();

     //calculate their mass ratio
     float mR = massB / massA;

     //calculate the axis of collision
     QVector2D collisionVector = posB - posA;
     collisionVector.normalize();

    //the proportion of each balls velocity along the axis of collision
     double vA = QVector2D::dotProduct(collisionVector, velA);
     double vB = QVector2D::dotProduct(collisionVector, velB);
     //the balls are moving away from each other so do nothing
     if (vA <= 0 && vB >= 0) {
        return;
     }

     //The velocity of each ball after a collision can be found by solving the quadratic equation
     //given by equating momentum and energy before and after the collision and finding the velocities
     //that satisfy this
     //-(mR+1)x^2 2*(mR*vB+vA)x -((mR-1)*vB^2+2*vA*vB)=0
     //first we find the discriminant
     double a = -(mR + 1);
     double b = 2 * (mR * vB + vA);
     double c = -((mR - 1) * vB * vB + 2 * vA * vB);
     double discriminant = sqrt(b * b - 4 * a * c);
     double root = (-b + discriminant)/(2 * a);
     //only one of the roots is the solution, the other pertains to the current velocities
     if (root - vB < 0.01) {
        root = (-b - discriminant)/(2 * a);
     }


    //The resulting changes in velocity for ball A and B
    QVector2D deltaVA = mR * (vB - root) * collisionVector;
    QVector2D deltaVB = (root - vB) * collisionVector;

    ballA->changeVelocity(deltaVA);
    ballB->changeVelocity(deltaVB);

}

bool StageTwoPlayableGame::isBreakable(Ball *ballA, Ball *ballB)
{
    // if not colliding (distance is larger than radii)
    //Properties of two colliding balls,
     //ball A
     QVector2D posA = ballA->getPosition();
     QVector2D velA = ballA->getVelocity();
     float massA = ballA->getMass();
     //and ball B
     QVector2D posB = ballB->getPosition();
     QVector2D velB = ballB->getVelocity();
     float massB = ballB->getMass();

     float mR = massB / massA;

     QVector2D collisionVector = posB - posA;
     collisionVector.normalize();
     double vA = QVector2D::dotProduct(collisionVector, velA);
     double vB = QVector2D::dotProduct(collisionVector, velB);
     if (vA <= 0 && vB >= 0) {
        return false;
     }
     double a = -(mR + 1);
     double b = 2 * (mR * vB + vA);
     double c = -((mR - 1) * vB * vB + 2 * vA * vB);
     double discriminant = sqrt(b * b - 4 * a * c);
     double root = (-b + discriminant)/(2 * a);
     //only one of the roots is the solution, the other pertains to the current velocities
     if (root - vB < 0.01) {
        root = (-b - discriminant)/(2 * a);
     }


    //The resulting changes in velocity for ball A and B
    QVector2D deltaVA = mR * (vB - root) * collisionVector;

    StageTwoBall *bA = dynamic_cast<StageTwoBall*>(ballA);
    float ballMass = bA->getMass();
    float ballStrength = bA->getStrength();
    QVector2D deltaV = deltaVA;
    float energyOfCollision = ballMass*deltaV.lengthSquared();
    return ballStrength < energyOfCollision;
}

bool StageTwoPlayableGame::isCollision(const Ball *ballA, const Ball *ballB) const
{
    return ballA->getPosition().distanceToPoint(ballB->getPosition()) <= ballA->getRadius() + ballB->getRadius();
}

void StageTwoPlayableGame::hitTheWhiteBall()
{
    //Properties of two colliding balls,
    //ball A
    QVector2D posA = whiteBall.lock()->getPosition();
    QVector2D velA = whiteBall.lock()->getVelocity();
    //and ball B is actually the cue lol
    QVector2D posB = mousePos;
    QVector2D velB = (posA - posB) / 3;

    //calculate their mass ratio
    float mR = 1;

    //calculate the axis of collision
    QVector2D collisionVector = posB - posA;
    collisionVector.normalize();

   //the proportion of each balls velocity along the axis of collision
    double vA = QVector2D::dotProduct(collisionVector, velA);
    double vB = QVector2D::dotProduct(collisionVector, velB);
    //the balls are moving away from each other so do nothing
    if (vA <= 0 && vB >= 0) {
        return;
    }

    //The velocity of each ball after a collision can be found by solving the quadratic equation
    //given by equating momentum and energy before and after the collision and finding the velocities
    //that satisfy this
    //-(mR+1)x^2 2*(mR*vB+vA)x -((mR-1)*vB^2+2*vA*vB)=0
    //first we find the discriminant
    double a = -(mR + 1);
    double b = 2 * (mR * vB + vA);
    double c = -((mR - 1) * vB * vB + 2 * vA * vB);
    double discriminant = sqrt(b * b - 4 * a * c);
    double root = (-b + discriminant)/(2 * a);
    //only one of the roots is the solution, the other pertains to the current velocities
    if (root - vB < 0.01) {
      root = (-b - discriminant)/(2 * a);
    }


    //The resulting changes in velocity for the cue ball
    whiteBall.lock()->changeVelocity(mR * (vB - root) * collisionVector);

}


