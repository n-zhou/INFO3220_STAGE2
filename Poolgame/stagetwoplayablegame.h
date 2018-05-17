#pragma once

#include <memory>
#include "abstractplayablegame.h"
#include "ball.h"
#include "table.h"
#include "game.h"
#include "stagetwoball.h"
#include <cmath>
#include <iostream>
#include <algorithm>

/**
 * @brief The StageTwoPlayableGame class is the Stage 2 implementation
 * of the {@code AbstractPlayableGame}. It overrides most of the optional
 * mouse events and implements all of the pure virtual methods.
 *
 * <p>
 * This implementation of AbstractPlayableGame is not thread safe. This class
 * makes no guarantees of correctness in a multithreaded envirnoment. For a
 * thread safe implementation please look in the proof of P=NP.
 * </p>
 *
 * @author nzho8446
 * @see AbstractPlayableGame
 * @since Stage 2
 */

class StageTwoPlayableGame : public AbstractPlayableGame {
public:
    StageTwoPlayableGame(std::unique_ptr<Table> table, std::vector<std::shared_ptr<Ball>> &balls);

    /**
     * @brief ~StageTwoPlayableGame
     */
    virtual ~StageTwoPlayableGame() {}

    /**
     * @brief rightClick - this method should be called whenever
     * a there is a rightclick mouse event.
     * @param e - The QMouseEvent associated with the rightclick
     */
    virtual void rightClick(QMouseEvent *e) override;

    /**
     * @brief leftClick - this method should be called whenever
     * a there is a leftclick mouse event. The Default behaviour
     * of this method is to ignore it so it is recommended that subclasses
     * override this behaviour.
     *
     * @param e - The QMouseEvent associated with releasing the left click
     */
    virtual void leftClick(QMouseEvent *e) override;

    /**
     * @brief leftClickRelease - this method is called whenever the
     * left mouse button is released.
     *
     * @param e - The QMouseEvent associated with the releasing the
     * leftclick.
     */
    virtual void leftClickRelease(QMouseEvent *e) override;

    /**
     * @brief mouseDrag - this method is called whenever the user moves
     * the mouse around. This method assumes that the QMouseEvent from the
     * dialog class has tracking turned on.
     *
     * @param e - The QMouseEvent associated with moving the mouse.
     */
    virtual void mouseDrag(QMouseEvent *e) override;

    /**
     * @brief keyPressEvent
     * @param event - the QKeyEvent associated with the keypress
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief render - Draws the game onto the screen
     * @param painter - QPainter used to draw the objects with
     */
    virtual void render(QPainter &painter) override;

    /**
     * @brief animate
     * @param dt - the number of seconds between each call of this
     * method
     * XXX
     */
    virtual void animate(double dt) override;

    /**
     * @brief getMinimumHeight
     * @return the minimum height required for the window
     * to be to display the objects in the game
     */
    virtual int getMinimumHeight() const  override;

    /**
     * @brief getMinimumWidth
     * @return the minimum width requried for the window
     * to be to display the objects in the game
     */
    virtual int getMinimumWidth() const  override;

protected:
    std::unique_ptr<Table> m_table;
    std::vector<std::shared_ptr<Ball>> m_balls;

    /**
     * @brief resolveCollision - modify the ball's velocity if it is colliding with the table
     * @param table - the table to be bounds checked
     * @param ball - the ball to move
     */
    virtual void resolveCollision(Table *table, Ball *ball);

    /**
     * @brief resolveCollision - resolve both ball's velocity whether these balls collide. If either
     * ball breaks due to a collision, they will be removed from the game completely(hopefully).
     * @param ballA - first ball
     * @param ballB - second ball
     */
    virtual void resolveCollision(std::shared_ptr<Ball> ballA, std::shared_ptr<Ball> ballB);

    /**
     * @brief render - a method for forcing balls to draw the parent only
     * @param painter - the QPainter used to draw the ball
     * @param ball - a pointer to the ball to be drawn
     */
    virtual void render(QPainter &painter, Ball *ball);

    /**
     * @brief hitTheWhiteBall - applies the change in velocity
     * to the white ball that is a result of getting hit by the cue.
     */
    virtual void hitTheWhiteBall();

private:
    /**
     * @brief m_clicked - a boolean value to determine whether or not the
     * user is allowed to be aiming. If the user left clicks while the white ball
     * is not moving m_click should be <tt>true</tt>, and if they release or the whiteball
     * doesn't remain stationary, this should be <tt>false</tt>.
     */
    bool m_clicked;

    /**
     * @brief m_whiteBall - a weak pointer to a white ball
     * (if one exists)
     */
    std::weak_ptr<Ball> m_whiteBall;

    /**
     * @brief m_mousePos - a QVector2D containing the (x, y) qt coordinates
     * of the mouse position. This is to be updated in the mouse event methods.
     */
    QVector2D m_mousePos;

    /**
     * @brief m_toggle - a boolean used to determine whether to draw
     * children balls on top of their parents.
     */
    bool m_toggle;

    /**
     * @brief isCollision - is a method used to determine whether
     * a ball collides with the side of a table. This method can be
     * used as a predicate for the method resolveCollision(Table*, Ball*)
     * @param table - the table we want to that the ball collides with
     * @param b - the ball we want to check
     * @return <tt>true</tt> if and only if the ball collides
     * with the sides of the table.
     */
    bool isCollision(const Table *table, const Ball *b) const;
};
