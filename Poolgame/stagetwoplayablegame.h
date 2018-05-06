#pragma once

#include <memory>
#include "abstractplayablegame.h"
#include "ball.h"
#include "table.h"
#include "game.h"
#include <cmath>
#include <iostream>
#include <algorithm>

class StageTwoPlayableGame : public AbstractPlayableGame
{
public:
    StageTwoPlayableGame(Table *table, std::vector<std::shared_ptr<Ball>> *balls)
        : AbstractPlayableGame(), m_table(table), m_balls(balls), m_clicked(false)
    {
        for (auto b : *m_balls) {
            if (b.get()->getColour() == QColor("white")) {
                whiteBall = b;
                break;
            }
        }
    }

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
        std::cout << whiteBall.use_count() << std::endl;
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

    bool inPocket(std::shared_ptr<Ball> const& b);

private:
    Table *m_table;
    std::vector<std::shared_ptr<Ball>> *m_balls;
    bool m_clicked;
    std::weak_ptr<Ball> whiteBall;
    QVector2D mousePos;


    void resolveCollision(Table *, Ball *);

    void resolveCollision(Ball*ballA, Ball*ballB);

    /**
     * @brief hitTheWhiteBall - applies the change in velocity
     * to the white ball that is a result of getting hit by the cue.
     */
    void hitTheWhiteBall();
};


/*
    progress_bar = new QProgressBar(this);
    progress_bar->setVisible(true);
    progress_bar->resize(game->getMinimumWidth(), 20);
    progress_bar->move(0, game->getMinimumHeight());
    progress_bar->setAlignment(Qt::AlignCenter);
    progress_bar->setValue(0);
*/
