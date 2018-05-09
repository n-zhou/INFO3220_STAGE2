#pragma once

#include <QColor>
#include <QPoint>
#include <QPainter>
#include <QVector2D>

/**
 * @brief The Ball class represents a ball object.
 *
 * @author "James Butcher"
 * @author nzho8446
 * @since Stage 1
 */

class Ball {
protected:
    QBrush m_brush;
    QVector2D m_pos;
    QVector2D m_velocity;
    double m_mass;
    int m_radius;
public:

    static bool toggle;

    virtual ~Ball() {}
    Ball(QColor colour,
         QVector2D position,
         QVector2D velocity,
         double mass,
         int radius) :
        m_brush(colour),
        m_pos(position),
        m_velocity(velocity),
        m_mass(mass),
        m_radius(radius) {}

    /**
     * @brief render - draw the ball to the screen
     * @param painter - QPainter that is owned by the dialog
     */
    virtual void render(QPainter &painter) = 0;

    /**
     * @brief translate - Move the ball's position by provided vector
     * @param vec - vector
     */
    virtual void translate(QVector2D vec) = 0;

    QVector2D getVelocity() const { return m_velocity; }

    /**
     * @brief changeVelocity - modify speed by a constant amount
     * @param delta - change in velocity (x,y)
     */
    void changeVelocity(const QVector2D& delta) { m_velocity += delta; }

    /**
     * @brief multiplyVelocity - apply vector multiplicatively
     * @param vel - vector
     */
    void multiplyVelocity(const QVector2D& vel) { m_velocity *= vel; }
    virtual double getMass() const { return m_mass; }
    double getRadius() const { return m_radius; }
    QVector2D getPosition() const { return m_pos; }
    QColor getColour() const { return m_brush.color(); }
};

class StageOneBall : public Ball {
public:
    StageOneBall(QColor colour, QVector2D position,
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
};
