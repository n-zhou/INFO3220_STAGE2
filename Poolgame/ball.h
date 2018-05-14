#pragma once

#include <QColor>
#include <QPoint>
#include <QPainter>
#include <QVector2D>

/**
 * @brief The Ball class represents a ball object.
 *
 * <p>
 * Perhaps, the most significant change is adding virtual to the
 * getMass() method. Besides that, there are some slight changes
 * to indenting, this class remains unchanged from stage 1.
 * </p>
 *
 * @author "James Butcher"
 * @author nzho8446
 * @see StageOneBall
 * @see StageTwoBall
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
    virtual ~Ball() {}
    Ball(QColor colour, QVector2D position,
         QVector2D velocity, double mass, int radius) :
        m_brush(colour), m_pos(position), m_velocity(velocity),
        m_mass(mass), m_radius(radius) {}

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

    /**
     * @brief getVelocity
     * @return
     */
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

    /**
     * @brief getMass returns the mass of the ball. This method
     * has been marked virtual since Stage2.
     * @return - the mass of the ball
     */
    virtual double getMass() const { return m_mass; }
    double getRadius() const { return m_radius; }
    QVector2D getPosition() const { return m_pos; }
    QColor getColour() const { return m_brush.color(); }

};

/**
 * @brief The StageOneBall class implements the Ball interface. This
 * implementation works fine for stage 1 configuration files.
 *
 * <p>
 * StageOneBall implements the pure virtual methods from Ball (render()
 * and translate()). No other method is overriden. The constructor of
 * StageOneBall shares the same constuctor as Ball.
 * </p>
 *
 * <p>
 * For configuration files that use a stage later than one or needs
 * the ball to do features not required in stage one, use an alternative
 * concrete implementation of  Ball.
 * </p>
 *
 * @author "James Butcher"
 * @see StageTwoBall
 * @since Stage 1
 */

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
