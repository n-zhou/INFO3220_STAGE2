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

class StageOneAdaptor : public AbstractPlayableGame {
public:
    StageOneAdaptor(Game *game) :
        AbstractPlayableGame(), m_game(game) {}

    /* delete the only object we manage */
    virtual ~StageOneAdaptor() {
        delete m_game;
    }

    /**
     * @brief render - Draws the game onto the screen
     * @param painter - QPainter used to draw the objects with
     */
    virtual void render(QPainter &painter) override;

    /**
     * @brief animate - applys the physics to the game based on
     * the paramater dt (delta t).
     * @param dt - the number of seconds between each call of this method.
     */
    virtual void animate(double dt) override;

    /* how large the window's width should at least be */
    virtual int getMinimumHeight() const override;

    /* how large the window's height should at least be */
    virtual int getMinimumWidth() const override;

private:
    Game *m_game;
};


