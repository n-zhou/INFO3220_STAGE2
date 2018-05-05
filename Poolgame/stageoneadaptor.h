#pragma once

#include "abstractplayablegame.h"
#include "game.h"

class StageOneAdaptor : public AbstractPlayableGame
{
public:
    StageOneAdaptor(Game *game) : AbstractPlayableGame(),
        m_game(game) {}

    ~StageOneAdaptor()
    {
        delete m_game;
    }

    void render(QPainter &painter);

    void animate(double dt);

    int getMinimumHeight() const;

    int getMinimumWidth() const;

private:
    Game *m_game;
};


