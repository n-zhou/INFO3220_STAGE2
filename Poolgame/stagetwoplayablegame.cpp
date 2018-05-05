#include "stagetwoplayablegame.h"


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
    QVector2D velocity = whiteBall->getVelocity();
    //we allow an epsilon on 2 when deciding whether the white ball is stationary
    if (std::fabs(velocity.x()) > 2 || std::fabs(velocity.y()) > 2) {
        std::cout << "You can only hit the cue when it's not moving!" << std::endl;
        return;
    }
    m_clicked = true;
}

void StageTwoPlayableGame::leftClickRelease(QMouseEvent *e)
{
    if (m_clicked) {
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
    if (m_clicked) {
        //thickness of the line is set to illustrate power of shot
        double distance = whiteBall->getPosition().distanceToPoint(mousePos);
        int thickness = std::fmin(distance/60, 10);
        painter.setPen(QPen(Qt::black, thickness, Qt::DotLine, Qt::RoundCap));
        painter.drawLine(whiteBall->getPosition().toPointF(), mousePos.toPointF());
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

#include <QDebug>
void StageTwoPlayableGame::animate(double dt){

    for (auto it = m_balls->begin(); it != m_balls->end(); ++it) {
        std::shared_ptr<Ball> ballA = *it;
        // correct ball velocity if colliding with table
        Game::resolveCollision(m_table, ballA.get());
        // check collision with all later balls
        for (auto nestedIt = it + 1; nestedIt != m_balls->end(); ++nestedIt) {
            std::shared_ptr<Ball> ballB = *nestedIt;
            Game::resolveCollision(ballA.get(), ballB.get());
        }

        // move ball due to speed
        ballA->translate(ballA->getVelocity() * dt);
        // apply frictionz
        ballA->changeVelocity(-ballA->getVelocity() * m_table->getFriction() * dt);


    }

}

void StageTwoPlayableGame::resolveCollision(Table *table, Ball *ball)
{

}

void StageTwoPlayableGame::resolveCollision(Ball *b1, Ball *b2)
{

}

void StageTwoPlayableGame::hitTheWhiteBall()
{
    //Properties of two colliding balls,
    //ball A
    QVector2D posA = whiteBall->getPosition();
    QVector2D velA = whiteBall->getVelocity();
    float massA = whiteBall->getMass();
    //and ball B is actually the cue lol
    QVector2D posB = mousePos;
    QVector2D velB = (posA - mousePos) / 10;
    float massB = 10;

    //calculate their mass ratio
    float mR = massB / massA;

    //calculate the axis of collision
    QVector2D collisionVector = posB / posA;
    collisionVector.normalize();

   //the proportion of each balls velocity along the axis of collision
    double vA = QVector2D::dotProduct(collisionVector, velA);
    double vB = QVector2D::dotProduct(collisionVector, velB);
    //the balls are moving away from each other so do nothing
    if (vA <= 0 && vB >= 0) {
        std::cout << "fug" << std::endl;
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
    whiteBall->changeVelocity(mR * (vB - root) * collisionVector);
    //since Ball B is not a real ball we don't actually change the velocity
    //QVector2D deltaVB = (root - vB) * collisionVector;
}




