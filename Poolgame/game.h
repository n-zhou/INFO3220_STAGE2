#pragma once

#include <QJsonObject>
#include "abstractstagefactory.h"

/**
 * @brief The Game class represents a stage 1 game.
 *
 * <p>
 * This class has been modified from holding raw pointers to holding
 * smart pointers. This makes memory management automated.
 * </p>
 *
 * <p>
 * It is not recommended to extend this class. It is faily limited in extensiblity
 * as none of the methods are marked virtual. It also doesn't handle mouse events
 * that are caused by the user limiting interactiveness.
 * </p>
 *
 * @author "James Butcher"
 * @author nzho8446
 * @see StageOneAdaptor
 * @since Stage 1
 */
class Game {
    std::vector<std::shared_ptr<Ball>> m_balls;
    std::unique_ptr<Table> m_table;
public:
    virtual ~Game();
    Game(std::vector<std::shared_ptr<Ball>> &balls, std::unique_ptr<Table> &table) :
        m_balls(balls), m_table(table.release()){}

    /**
     * @brief Draws all owned objects to the screen (balls and table)
     * @param painter - qtpainter to blit to screen with
     */
    void render(QPainter& painter) const;

    /**
     * @brief Updates the positions of all objects within, based on how much time has changed
     * @param dt - time elapsed since last frame in seconds
     */
    [[deprecated("This method does not implement pixels per seconds properly")]]
    void animate(double dt);

    /* how large the window's width should at least be */
    int getMinimumWidth() const { return m_table->getWidth(); }
    /* how large the window's height should at least be */
    int getMinimumHeight() const { return m_table->getHeight(); }

    /**
     * @brief resolveCollision - modify the ball's velocity if it is colliding with the table
     * @param table - the table to be bounds checked
     * @param ball - the ball to move
     */
    void resolveCollision(const Table* table, Ball* ball);

    /**
     * @brief resolveCollision - resolve both ball's velocity whether these balls collide
     * @param ballA - first ball
     * @param ballB - second ball
     */
     void resolveCollision(Ball* ballA, Ball* ballB);
};
