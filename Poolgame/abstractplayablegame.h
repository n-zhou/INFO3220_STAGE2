#pragma once

#include <QMouseEvent>
#include <QPainter>
#include <QKeyEvent>

/**
 * @brief The AbstractPlayableGame class represents a playable
 * game instance of pool.
 *
 * <p>
 * The mouse interactions in this class by default do nothing. The
 * reason it does nothing by default, is to maximise compatability
 * with stage 1. In Stage 1, there was no way to interact with the
 * game.
 * </p>
 *
 * <p>
 * Any subclass of this class should override the methods involving the
 * mouse and keyboard should they wish to include interaction. Should they
 * not override those methods, the default behaviour would be to do nothing.
 * </p>
 *
 * @author nzho8446
 * @see Ball
 * @see Table
 * @since stage2
 */

class AbstractPlayableGame {
public:
    AbstractPlayableGame() {}

    virtual ~AbstractPlayableGame() {}

    /**
     * @brief rightClick - this method should be called whenever
     * a there is a rightclick mouse event.
     */
    virtual void rightClick(QMouseEvent *) {}

    /**
     * @brief rightClickRelease - this method is called whenever the rightclick
     * is released.
     */
    virtual void rightClickRelease(QMouseEvent *) {}

    /**
     * @brief leftClick - this method should be called whenever
     * a there is a leftclick mouse event.
     */
    virtual void leftClick(QMouseEvent *) {}

    /**
     * @brief leftClickRelease - this method is called whenever the
     * left mouse button is released.
     */
    virtual void leftClickRelease(QMouseEvent *) {}

    /**
     * @brief mouseDrag - this method is called whenever the user moves
     * the mouse around.
     */
    virtual void mouseDrag(QMouseEvent *) {}

    /**
     * @brief keyPressEvent - called whenever the user hits a key on their
     * keyboard
     */

    virtual void keyPressEvent(QKeyEvent *) {}

    /**
     * @brief keyReleaseEvent - called whenever the user releases
     * a keypress.
     */
    virtual void keyReleaseEvent(QKeyEvent *) {}


    /**
     * @brief render - Draws the game onto the screen
     * @param painter - QPainter used to draw the objects with
     */
    virtual void render(QPainter &painter) = 0;

    /**
     * @brief animate - applys the physics to the game based on
     * the paramater dt (delta t).
     * @param dt - the number of seconds between each call of this method.
     */
    virtual void animate(double dt) = 0;

    /**
     * @brief getMinimumHeight
     *
     * @return the minimum height required for the window
     * to be to display the objects in the game
     */
    virtual int getMinimumHeight() const = 0;

    /**
     * @brief getMinimumWidth
     *
     * @return the minimum width requried for the window
     * to be to display the objects in the game
     */
    virtual int getMinimumWidth() const = 0;


};
