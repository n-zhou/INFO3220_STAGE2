#ifndef STAGEONEADAPTOR_H
#define STAGEONEADAPTOR_H

#include "abstractplayablegame.h"

class StageOneAdaptor : AbstractPlayableGame
{
public:
    StageOneAdaptor(Game *game)
        : m_game(game) {}

    ~StageOneAdaptor()
    {
        delete m_game;
    }

    void render(QPainter &painter)
    {
        m_game->render(painter);
    }

    void animate(double dt)
    {
        m_game->animate(dt);
    }


private:
    Game *m_game;
};

#endif // STAGEONEADAPTOR_H
