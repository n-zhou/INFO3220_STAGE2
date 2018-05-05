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

}

void StageTwoPlayableGame::leftClickRelease(QMouseEvent *e)
{

}

void StageTwoPlayableGame::render(QPainter &painter)
{
    m_table->render(painter);
    for (std::shared_ptr<Ball> b : *m_balls) {
        b.get()->render(painter);
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
        // apply friction
        ballA->changeVelocity(-ballA->getVelocity() * m_table->getFriction() * dt);

        QVector2D ballAVelocity = ballA->getVelocity();
        if (std::fabs(ballAVelocity.y() < 1)) {
            ballA->getVelocity().setY(0);
        }
        if (std::fabs(ballAVelocity.x() < 1)) {
            ballA->getVelocity().setX(0);
        }
    }

}



