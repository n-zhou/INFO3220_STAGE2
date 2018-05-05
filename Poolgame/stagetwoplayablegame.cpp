#include "stagetwoplayablegame.h"


void StageTwoPlayableGame::rightClick(QMouseEvent *e)
{

}

void StageTwoPlayableGame::rightClickRelease(QMouseEvent *e)
{

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

void StageTwoPlayableGame::animate(double dt){


}

int StageTwoPlayableGame::getMinimumHeight() const
{
    return m_table->getHeight();
}

int StageTwoPlayableGame::getMinimumWidth() const
{
    return m_table->getWidth();
}
