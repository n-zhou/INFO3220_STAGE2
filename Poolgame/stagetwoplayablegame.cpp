#include "stagetwoplayablegame.h"
#include <string>

void draw(QPainter &painter, Ball &ball);

StageTwoPlayableGame::StageTwoPlayableGame(std::unique_ptr<Table> table, std::vector<std::shared_ptr<Ball>> &balls)
    : AbstractPlayableGame(), m_table(std::move(table)), m_balls(balls), m_clicked(false), m_toggle(false)
{
    //set the white ball
    for (auto b : m_balls) {
        if (b->getColour() == QColor("white")) {
            m_whiteBall = b;
            break;
        }
    }

    //remove out of bounds ball
    for (auto i = m_balls.begin(); i != m_balls.end(); ++i) {
        std::shared_ptr<Ball> b = *i;
        if (isCollision(m_table.get(), b.get())) {
            m_balls.erase(i--);
        }
    }
}

void StageTwoPlayableGame::rightClick(QMouseEvent *e) {
    //toggles the visibility of the inner balls on
    m_toggle = !m_toggle;
}

void StageTwoPlayableGame::leftClick(QMouseEvent *e) {
    if (m_whiteBall.expired()) {
        return;
    }
    QVector2D velocity = m_whiteBall.lock()->getVelocity();
    //we allow an epsilon on 2 when deciding whether the white ball is stationary
    if (std::fabs(velocity.x()) > 2 || std::fabs(velocity.y()) > 2) {
        std::cout << "You can only hit the cue when it's not moving!" << std::endl;
        return;
    }
    m_mousePos = QVector2D(e->localPos());
    if (m_whiteBall.lock()->getPosition().distanceToPoint(m_mousePos) <= m_whiteBall.lock()->getRadius()) {
        m_clicked = true;
    }
}

void StageTwoPlayableGame::leftClickRelease(QMouseEvent *e) {
    if (m_clicked && !m_whiteBall.expired()) {
        m_mousePos = QVector2D(e->localPos());
        hitTheWhiteBall();
        m_clicked = false;
    }
}

void StageTwoPlayableGame::mouseDrag(QMouseEvent *e) {
    if (m_clicked && !m_whiteBall.expired()) {
        m_mousePos = QVector2D(e->localPos());
    }
}

void StageTwoPlayableGame::keyPressEvent(QKeyEvent *event) {
    std::string key = event->text().toStdString();
    if (key == "s" || key == "S") {
        if (!m_whiteBall.expired()) {
            m_whiteBall.lock()->multiplyVelocity(QVector2D(0, 0));
            std::cout << "YOU STOPPED THE WHITE BALL YOU CHEATER" << std::endl;
        } else {
            std::cout << "Can't stop the white ball when it's pocketed :(" << std::endl;
        }
    }

    //we'll place a new white ball in the game just because the user pressed control
    if (event->key() == Qt::Key_Control) {
        m_balls.push_back(std::shared_ptr<Ball>(
                              new StageTwoBall(QColor("white"), QVector2D(100, 100),QVector2D(0, 0),
                                               Default::Ball::mass, Default::Ball::radius, Default::Ball::strength)
                              ));
        m_whiteBall = m_balls.back();
    }
}

void StageTwoPlayableGame::render(QPainter &painter) {
    m_table->render(painter);

    for (std::shared_ptr<Ball> b : m_balls) {
        //we check if the visibility of the children balls is toggled on
        if (m_toggle) {
            //the parent balls will draw themselves, and then recursively draw their children
            b->render(painter);
        } else {
            //else we draw the parent ball only
            this->render(painter, b.get());
        }

    }

    //draws the line while the left mouse button is clicked and aiming is on
    if (m_clicked && !m_whiteBall.expired()) {
        //thickness of the line is set to illustrate power of shot
        painter.save();
        double distance = m_whiteBall.lock()->getPosition().distanceToPoint(m_mousePos);
        int thickness = std::fmin(distance/60, 10);
        painter.setPen(QPen(Qt::black, thickness, Qt::DotLine, Qt::RoundCap));
        painter.drawLine(m_whiteBall.lock()->getPosition().toPointF(), m_mousePos.toPointF());
        painter.restore();
    }
}

int StageTwoPlayableGame::getMinimumHeight() const {
    return m_table->getHeight();
}

int StageTwoPlayableGame::getMinimumWidth() const {
    return m_table->getWidth();
}

void StageTwoPlayableGame::animate(double dt) {

    //remove balls that are encompassed in pockets
    for (auto &pocket : m_table->getPockets()) {
        /* we start from the back to avoid too much element shifting. Also using auto instead of int is a bad idea */
        for (int i = m_balls.size()-1; i >= 0; --i) {
            std::shared_ptr<Ball> ball = m_balls.at(i);
            if (ball->getPosition().distanceToPoint(pocket->getPos()) + ball->getRadius() <= pocket->getRadius()) {
                m_balls.erase(m_balls.begin() + i);
            }
        }
    }

    /* we iterate from the end so children balls added from parent balls breaking
     * will not cause a the loop to iterate more than it needs to */
    for (int it = m_balls.size()-1; it >= 0; --it) {
        std::weak_ptr<Ball> ballA = m_balls[it];
        // check collision with all earlier balls
        for (int nestedIt = it - 1; nestedIt >= 0; ) {
            std::weak_ptr<Ball> ballB = m_balls[nestedIt];
            resolveCollision(ballA.lock(), ballB.lock());
            if (ballA.expired() && ballB.expired()) {
                //we need to decrement by 2 since both balls broke
                ballA = m_balls[(it -= 2)]; //doing more than one assignent in a single statement is dangerous ;)
                nestedIt = it - 1;
            } else if (ballA.expired()) {
                //we must decrement it by 1 since the original ballA broke
                ballA = m_balls[--it];
                nestedIt = it - 1;
            } else if (ballB.expired()){
                --it;
                --nestedIt;
            } else {
                --nestedIt;
            }

        }
        //create a shared pointer so we don't need to call lock to every time we want to access the ballA
        std::shared_ptr<Ball> ball = ballA.lock();
        resolveCollision(m_table.get(), ball.get());
        // move ball due to speed
        ball->translate(ball->getVelocity() * dt);

        /* set the velocity of the ball to 0 if it's close enough to 0 to avoid
         * weird floating point behaviour and NaN errors  */
        if (std::fabs(ball->getVelocity().x()) < 3 && std::fabs(ball->getVelocity().y()) < 3) {
            ballA.lock()->multiplyVelocity(QVector2D(0, 0));
            continue;
        }
        // apply frictionz
        ball->changeVelocity(-ball->getVelocity() * m_table->getFriction() * dt);
    }

    if (!m_whiteBall.expired()) {
        QVector2D vel = m_whiteBall.lock()->getVelocity();
        if (!qFuzzyCompare(vel, QVector2D(0, 0))) {
            //if the ball moved during aiming, we will remove control from the player
            m_clicked = false;
        }
    }

}

bool StageTwoPlayableGame::isCollision(const Table *table, const Ball *b) const
{
    QVector2D bPos = b->getPosition();

    if (bPos.x() + b->getRadius() > table->getWidth()) {
        return true;
    } else if (bPos.x() - b->getRadius() < 0) {
        return true;
    } else if (bPos.y() + b->getRadius() > table->getHeight()) {
        return true;
    } else if (bPos.y() - b->getRadius() < 0) {
        return true;
    }

    return false;
}

void StageTwoPlayableGame::resolveCollision(Table *table, Ball *ball) {
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

void StageTwoPlayableGame::resolveCollision(std::shared_ptr<Ball> ballA, std::shared_ptr<Ball> ballB) {
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
    QVector2D deltaVA = mr * (pb - root) * collisionVector;
    QVector2D deltaVB = (root-pb) * collisionVector;

    StageTwoBall *bA = dynamic_cast<StageTwoBall*>(ballA.get());
    float ballMass = ballA->getMass();
    /* if the cast was successful we can get the strength from the pointer bA, otherwise we will assume infinity */
    float ballStrength = (bA) ? bA->getStrength() : Default::Ball::strength;
    float ballRadius = ballA->getRadius();
    QVector2D preCollisionVelocity = ballA->getVelocity();
    QVector2D deltaV = deltaVA;
    float energyOfCollision = ballMass*deltaV.lengthSquared();
    //update the velocity of the parent ball regardless of whether or not it breaks
    ballA->changeVelocity(deltaVA);
    if (ballStrength < energyOfCollision) {
        float energyPerBall = energyOfCollision/bA->getBalls().size();
        QVector2D pointOfCollision((-deltaV.normalized())*ballRadius);
        //for each component ball
        for (auto b : bA->getBalls()) {
            QVector2D componentBallVelocity = preCollisionVelocity +
                    sqrt(energyPerBall/b->getMass())*(b->getPosition()-pointOfCollision).normalized();
            b->changeVelocity(componentBallVelocity);
            m_balls.push_back(b);
        };
        //erase ballA from our vector of balls since it broke
        m_balls.erase(std::remove(m_balls.begin(), m_balls.end(), ballA),
                      m_balls.end());
    }

    //apply the same thing to ballB
    StageTwoBall *bB = dynamic_cast<StageTwoBall*>(ballB.get());
    ballStrength = (bB) ? bB->getStrength() : Default::Ball::strength;
    preCollisionVelocity = ballB->getVelocity();
    energyOfCollision = ballB->getMass()*deltaVB.lengthSquared();
    //update the velocity of the parent ball regardless of whether or not it breaks
    ballB->changeVelocity(deltaVB);
    if (ballStrength < energyOfCollision) {
        float energyPerBall = energyOfCollision/bB->getBalls().size();
        QVector2D pointOfCollision((-deltaVB.normalized())*ballB->getRadius());
        //for each component ball
        for (auto b : bB->getBalls()) {
            QVector2D componentBallVelocity = preCollisionVelocity +
                    sqrt(energyPerBall/b->getMass())*(b->getPosition()-pointOfCollision).normalized();
            b->changeVelocity(componentBallVelocity);
            m_balls.push_back(b);
        }
        //erase ballB from our vector of balls since it broke
        m_balls.erase(std::remove(m_balls.begin(), m_balls.end(), ballB),
                      m_balls.end());
    }
}

void StageTwoPlayableGame::hitTheWhiteBall() {
    /* The following code is sourced from Assignment 1 and
     * has been modified to fullfill the purpose of a cue
     * hitting the white ball */

    //Properties of a white ball and "cue"
    //ball A
    QVector2D posA = m_whiteBall.lock()->getPosition();
    QVector2D velA = m_whiteBall.lock()->getVelocity();
    //and properties of the cue
    QVector2D posB = m_mousePos;
    /* A vector going from B->A is calculated A-B.
    We divide this velocity by a scalar 1.2 to make sure
    the velocity of the hit doesn't get out of control */
    QVector2D velB = (posA - posB) / 1.2;

    /* we set the mass ratio equal to one so the resultant
     * velocity is the same no matter what the mass of the cue
     * ball is */
    float mR = 1;
    QVector2D collisionVector = posB - posA;
    collisionVector.normalize();
    double vA = QVector2D::dotProduct(collisionVector, velA);
    double vB = QVector2D::dotProduct(collisionVector, velB);
    if (vA <= 0 && vB >= 0) {
        return;
    }
    double a = -(mR + 1);
    double b = 2 * (mR * vB + vA);
    double c = -((mR - 1) * vB * vB + 2 * vA * vB);
    double discriminant = sqrt(b * b - 4 * a * c);
    double root = (-b + discriminant)/(2 * a);
    if (root - vB < 0.01) {
        root = (-b - discriminant)/(2 * a);
    }
    //The resulting changes in velocity for the cue ball
    m_whiteBall.lock()->changeVelocity(mR * (vB - root) * collisionVector);
}

void StageTwoPlayableGame::render(QPainter &painter, Ball *ball) {
    painter.save();
    painter.setBrush(ball->getColour());
    painter.drawEllipse(ball->getPosition().toPointF(),
                        ball->getRadius(),
                        ball->getRadius());
    painter.restore();
}
