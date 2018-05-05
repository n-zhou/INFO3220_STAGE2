#pragma once

#include <memory>
#include "abstractplayablegame.h"
#include "ball.h"
#include "table.h"
#include "game.h"
#include <cmath>

class StageTwoPlayableGame : public AbstractPlayableGame
{
public:
    StageTwoPlayableGame(Table *table, std::vector<std::shared_ptr<Ball>> *balls)
        : AbstractPlayableGame(), m_table(table), m_balls(balls)
    {
        for (auto b : *m_balls) {
            if (b.get()->getColour() == QColor("white")) {
                whiteBall = b.get();
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
    Ball *whiteBall;

    void resolveCollision(Table *, Ball *);

    void resolveCollision(Ball&, Ball&);
};


/*
    progress_bar = new QProgressBar(this);
    progress_bar->setVisible(true);
    progress_bar->resize(game->getMinimumWidth(), 20);
    progress_bar->move(0, game->getMinimumHeight());
    progress_bar->setAlignment(Qt::AlignCenter);
    progress_bar->setValue(0);
*/
