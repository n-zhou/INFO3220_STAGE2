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
 *
 * </p>
 *
 * @author nzho8446
 * @see AbstractPlayableGame
 * @since Stage 2
 */

class StageTwoPlayableGame : public AbstractPlayableGame {
public:
    StageTwoPlayableGame(std::unique_ptr<Table> &table, std::vector<std::shared_ptr<Ball>> &balls);

    virtual ~StageTwoPlayableGame() {}

    /**
     * @brief rightClick - this method should be called whenever
     * a there is a rightclick mouse event. The Default behaviour
     * of this method is to ignore it so it is recommended that subclasses
     * override this behaviour.
     *
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
     * the mouse around.
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
     * @param dt
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
private:
    bool m_clicked;
    std::weak_ptr<Ball> m_whiteBall;
    QVector2D m_mousePos;
    bool m_toggle;

    bool isCollision(const Table *table, const Ball *b) const;

    void resolveCollision(Table *, Ball *);

    bool isCollision(const Ball *ballA, const Ball *ballB) const;

    bool isBreakable(Ball *ballA, Ball *ballB);

    void resolveCollision(Ball *ballA, Ball *ballB);

    std::vector<std::shared_ptr<Ball>> breakBall(Ball *ballA, Ball *ballB);

    void render(QPainter &painter, Ball *ball);

    /**
     * @brief hitTheWhiteBall - applies the change in velocity
     * to the white ball that is a result of getting hit by the cue.
     */
    void hitTheWhiteBall();
};
