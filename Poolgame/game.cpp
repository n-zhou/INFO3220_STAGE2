#include "game.h"
#include "utils.h"

#include <QJsonArray>
#include <stdexcept>
#include <cmath>

Game::~Game() {
    /** destructor body deleted since this class no longer
     * uses raw pointers to hold memory
     */
}

void Game::render(QPainter &painter) const {
    // table is rendered first, as its the lowest
    m_table->render(painter);
    // then render all the balls
    for (auto b : m_balls) b->render(painter);
}

void Game::animate(double dt) {
    // (test) collide the ball with each other ball exactly once
    // to achieve this, balls only check collisions with balls "after them"
    for (auto it = m_balls.begin(); it != m_balls.end(); ++it) {
        std::shared_ptr<Ball> ballA = *it;
        // correct ball velocity if colliding with table
        resolveCollision(m_table.get(), ballA.get());
        // check collision with all later balls
        for (auto nestedIt = it + 1; nestedIt != m_balls.end(); ++nestedIt) {
            std::shared_ptr<Ball> ballB = *nestedIt;
            resolveCollision(ballA.get(), ballB.get());
        }

        // move ball due to speed
        ballA->translate(ballA->getVelocity() * dt);
        // apply friction
        ballA->changeVelocity(-ballA->getVelocity() * m_table->getFriction() * dt);
    }
}

void Game::resolveCollision(const Table* table, Ball* ball) {
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

void Game::resolveCollision(Ball* ballA, Ball* ballB) {
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
