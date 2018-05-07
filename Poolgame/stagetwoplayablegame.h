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

#include <QDebug>
class StageTwoPlayableGame : public AbstractPlayableGame
{
public:
    StageTwoPlayableGame(Table *table, std::vector<std::shared_ptr<Ball>> *balls);

    ~StageTwoPlayableGame()
    {
        delete m_table;
        delete m_balls;
    }

    void rightClick(QMouseEvent *e);

    void rightClickRelease(QMouseEvent *e);

    void leftClick(QMouseEvent *e);

    void leftClickRelease(QMouseEvent *e);

    void mouseDrag(QMouseEvent *e);

    void keyPressEvent(QKeyEvent *event) {
        if (!whiteBall.expired()) {
            //whiteBall.lock()->multiplyVelocity(QVector2D(0, 0));
            qDebug() << whiteBall.lock()->getVelocity();
        }
    }

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

    int getMinimumHeight() const;

    int getMinimumWidth() const;

private:
    Table *m_table;
    std::vector<std::shared_ptr<Ball>> *m_balls;
    bool m_clicked;
    std::weak_ptr<Ball> whiteBall;
    QVector2D mousePos;

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
