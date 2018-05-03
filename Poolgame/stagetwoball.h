#ifndef STAGETWOBALL_H
#define STAGETWOBALL_H

#include "ball.h"
#include <vector>
#include <memory>
#include <QJsonArray>
#include <QJsonObject>

class StageTwoBall : public Ball
{
public:
    StageTwoBall(QColor colour, QVector2D position,
                 QVector2D velocity, double mass, int radius) :
        Ball(colour, position, velocity, mass, radius) {}

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
    void addBalls(QJsonObject &ballData);

private:
    std::vector<std::shared_ptr<Ball>> m_balls;
};

#endif // STAGETWOBALL_H
