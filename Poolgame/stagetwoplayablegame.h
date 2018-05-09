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
 * @brief The StageTwoPlayableGame class
 *
 * @author nzho8446
 * @see AbstractPlayableGame
 * @since Stage 2
 */

class StageTwoPlayableGame : public AbstractPlayableGame {
public:
    StageTwoPlayableGame(std::unique_ptr<Table> &table, std::vector<std::shared_ptr<Ball>> &balls);

    ~StageTwoPlayableGame() {}

    void rightClick(QMouseEvent *e);

    void rightClickRelease(QMouseEvent *e);

    void leftClick(QMouseEvent *e);

    void leftClickRelease(QMouseEvent *e);

    void mouseDrag(QMouseEvent *e);

    /**
     * @brief keyPressEvent
     * @param event - the QKeyEvent associated with the keypress
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief render - Draws the game onto the screen
     * @param painter - QPainter used to draw the objects with
     */
    void render(QPainter &painter);

    /**
     * @brief animate
     * @param dt
     */
    void animate(double dt);

    /**
     * @brief getMinimumHeight
     * @return the minimum height required for the window
     * to be to display the objects in the game
     */
    int getMinimumHeight() const;

    /**
     * @brief getMinimumWidth
     * @return the minimum width requried for the window
     * to be to display the objects in the game
     */
    int getMinimumWidth() const;

private:
    std::unique_ptr<Table> m_table;
    std::vector<std::shared_ptr<Ball>> m_balls;
    bool m_clicked;
    std::weak_ptr<Ball> m_whiteBall;
    QVector2D m_mousePos;

    bool isCollision(const Table *table, const Ball *b) const;

    void resolveCollision(Table *, Ball *);

    bool isCollision(const Ball *ballA, const Ball *ballB) const;

    bool isBreakable(Ball *ballA, Ball *ballB);

    void resolveCollision(Ball *ballA, Ball *ballB);

    std::vector<std::shared_ptr<Ball>>* breakBall(Ball *ballA, Ball *ballB);

    /**
     * @brief hitTheWhiteBall - applies the change in velocity
     * to the white ball that is a result of getting hit by the cue.
     */
    void hitTheWhiteBall();
};
