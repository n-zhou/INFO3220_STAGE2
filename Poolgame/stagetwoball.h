#pragma once

#include "ball.h"
#include "utils.h"
#include <vector>
#include <memory>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>

/**
 * @brief The StageTwoBall class
 *
 * @author nzho8446
 * @see Ball
 * @see StageOneBall
 * @since Stage 2
 */
class StageTwoBall : public Ball {
public:
    StageTwoBall(QColor colour,
                 QVector2D position,
                 QVector2D velocity,
                 double mass,
                 int radius,
                 double strength) :
        Ball(colour, position, velocity, mass, radius),
        m_balls(),
        m_strength(strength) {}

    ~StageTwoBall() {}

    /**
     * @brief render - draw the ball to the screen
     * @param painter - QPainter that is owned by the dialog
     */
    void render(QPainter &painter) override;

    /**
     * @brief translate - Move the ball's position by provided vector
     * @param vec - vector
     */
    void translate(QVector2D vec) override;

    /**
     * @brief addBalls - method not inherited from superclass Ball. This
     * method is used to add innerballs.
     * @param ballData
     */
    void addBall(std::shared_ptr<Ball> ball);

    /**
     * @brief getBalls - this method returns a vector containing
     * the balls inside this ball.
     * @return the vector containing the inner balls of this ball.
     */
    std::vector<std::shared_ptr<Ball>> &getBalls();

    /**
     * @brief getMass - returns the net total mass of this ball
     * @return the net total mass of this ball
     */
    double getMass() const override;

    /**
     * @brief getStrength returns the strength of the ball
     * @return the strength of the ball
     */
    double getStrength() const;

protected:
    std::vector<std::shared_ptr<Ball>> m_balls;
    double m_strength;
};

