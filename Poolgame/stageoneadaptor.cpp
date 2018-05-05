#include "stageoneadaptor.h"

void StageOneAdaptor::render(QPainter &painter)
{
    m_game->render(painter);
}

void StageOneAdaptor::animate(double dt)
{
    m_game->animate(dt);
}

/* how large the window's width should at least be */
int StageOneAdaptor::getMinimumWidth() const { return m_game->getMinimumWidth(); }
/* how large the window's height should at least be */
int StageOneAdaptor::getMinimumHeight() const { return m_game->getMinimumHeight(); }
