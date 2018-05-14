#pragma once

#include <QVector2D>
#include <QPainter>

/**
 * @brief The Pocket class represents a pocket in a pool game.
 * @author nzho8446
 * @see StageTwoPocket
 * @since Stage 2
 */
class Pocket {
public:
    Pocket(QVector2D pos, double radius) :
        m_pos(pos), m_radius(radius) {}

    virtual ~Pocket() {}

    /**
     * @brief render - draw the pockeet onto the screen using the specified painter
     * @param painter - the painter to use
     */
    virtual void render(QPainter& painter) = 0;

    virtual QVector2D getPos() { return m_pos; }
    virtual double getRadius() { return m_radius; }

protected:
    QVector2D m_pos;
    double m_radius;
};
