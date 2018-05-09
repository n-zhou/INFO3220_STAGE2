#pragma once

#include "abstractplayablegame.h"
#include "game.h"

/**
 * @brief The StageOneAdaptor class adapts the Game class
 * to be compatable with the AbstractPlayable game interface.
 * <p>
 * This class follows the Object adaptor variation of the
 * adaptor design pattern.
 * </p>
 * @author nzho8446
 * @see Game
 * @see AbstractPlayableGame
 */

class StageOneAdaptor : public AbstractPlayableGame
{
public:
    StageOneAdaptor(Game *game) : AbstractPlayableGame(),
        m_game(game) {}

    ~StageOneAdaptor() {
        delete m_game;
    }

    void render(QPainter &painter);

    void animate(double dt);

    int getMinimumHeight() const;

    int getMinimumWidth() const;

private:
    Game *m_game;
};


