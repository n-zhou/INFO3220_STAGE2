#pragma once

#include "ball.h"
#include "utils.h"
#include <vector>
#include <memory>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>

/**
 * @brief The StageTwoBall class represents a ball in the game of pool
 * which contains the ability to hold balls inside it as well as break apart.
 *
 * @author nzho8446
 * @see Ball
 * @see StageOneBall
 * @since Stage 2
 */

class StageTwoBall : public Ball {
public:
    StageTwoBall(QColor colour, QVector2D position, QVector2D velocity,
                 double mass, int radius, double strength) :
        Ball(colour, position, velocity, mass, radius),
        m_balls(), m_strength(strength) {}

    virtual ~StageTwoBall() {}

    /**
     * @brief render - draw the ball to the screen
     * @param painter - QPainter that is owned by the dialog
     */
    virtual void render(QPainter &painter) override;

    /**
     * @brief translate - Move the ball's position by provided vector
     * @param vec - vector
     */
    virtual void translate(QVector2D vec) override;

    /**
     * @brief addBall - adds an inner ball to this ball
     * @param ball - the ball we are going to contain in the parent
     * ball.
     */
    virtual void addBall(std::shared_ptr<Ball> ball);

    /**
     * @brief getMass - returns the net total mass of this ball
     * @return the net total mass of this ball
     */
    virtual double getMass() const override;

    std::vector<std::shared_ptr<Ball>> &getBalls();
    virtual double getStrength() const;

protected:
    std::vector<std::shared_ptr<Ball>> m_balls;
    double m_strength;
};

