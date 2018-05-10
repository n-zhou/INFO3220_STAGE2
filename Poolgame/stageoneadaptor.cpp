#include "stageoneadaptor.h"

void StageOneAdaptor::render(QPainter &painter) {
    m_game->render(painter);
}

void StageOneAdaptor::animate(double dt) {
    m_game->animate(1.0 / (dt*1000));
}

int StageOneAdaptor::getMinimumWidth() const { return m_game->getMinimumWidth(); }

int StageOneAdaptor::getMinimumHeight() const { return m_game->getMinimumHeight(); }
