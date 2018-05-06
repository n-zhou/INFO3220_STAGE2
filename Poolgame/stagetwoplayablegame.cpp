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

#include <QDebug>
void StageTwoPlayableGame::animate(double dt){

    //remove balls that are encompassed in pockets
    for (auto it = m_balls->begin(); it != m_balls->end(); ++it) {
        std::shared_ptr<Ball> ballA = *it;
        for (auto pocket : *(m_table->getPockets())) {
            if (ballA.get()->getPosition().distanceToPoint(pocket.get()->getPos()) + ballA.get()->getRadius() <= pocket.get()->getRadius()) {
                m_balls->erase(it--);
                break;
            }
        }
    }

    for (auto it = m_balls->begin(); it != m_balls->end(); ++it) {
        std::shared_ptr<Ball> ballA = *it;
        // correct ball velocity if colliding with table
        resolveCollision(m_table, ballA.get());
        // check collision with all later balls
        for (auto nestedIt = it + 1; nestedIt != m_balls->end(); ++nestedIt) {
            std::shared_ptr<Ball> ballB = *nestedIt;
            resolveCollision(ballA.get(), ballB.get());
        }

        // move ball due to speed
        ballA->translate(ballA->getVelocity() * dt);
        // apply frictionz
        ballA->changeVelocity(-ballA->getVelocity() * m_table->getFriction() * dt);


    }

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
    // SOURCE : ASSIGNMENT SPEC

    // if not colliding (distance is larger than radii)
    QVector2D collisionVector = ballB->getPosition() - ballA->getPosition();
    if (collisionVector.length() > ballA->getRadius() + ballB->getRadius()) return;
    collisionVector.normalize();

    float mr = ballB->getMass() / ballA->getMass();
    double pa = QVector2D::dotProduct(collisionVector, ballA->getVelocity());
    double pb = QVector2D::dotProduct(collisionVector, ballB->getVelocity());

    if (pa <= 0 && pb >= 0) return;

    double a = -(mr + 1);
    double b = 2*(mr * pb + pa);
    double c = -((mr - 1)*pb*pb + 2*pa*pb);
    double disc = sqrt(b*b - 4*a*c);
    double root = (-b + disc)/(2*a);
    if (root - pb < 0.01) {
        root = (-b - disc)/(2*a);
    }

    ballA->changeVelocity(mr * (pb - root) * collisionVector);
    ballB->changeVelocity((root-pb) * collisionVector);
}

void StageTwoPlayableGame::hitTheWhiteBall()
{
    //Properties of two colliding balls,
    //ball A
    QVector2D posA = whiteBall.lock()->getPosition();
    QVector2D velA = whiteBall.lock()->getVelocity();
    float massA = whiteBall.lock()->getMass();
    //and ball B is actually the cue lol
    QVector2D posB = mousePos;
    QVector2D velB = (posA - posB) / 10;
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
    whiteBall.lock()->changeVelocity(mR * (vB - root) * collisionVector);
    //since Ball B is not a real ball we don't actually change the velocity
    //QVector2D deltaVB = (root - vB) * collisionVector;
}

bool StageTwoPlayableGame::inPocket(std::shared_ptr<Ball> const& b)
{
    for (auto p : *(m_table->getPockets())) {
        if (b.get()->getPosition().distanceToPoint(p.get()->getPos()) + b.get()->getRadius() <= p.get()->getRadius()) {
            return true;
        }
    }
    return false;
}


