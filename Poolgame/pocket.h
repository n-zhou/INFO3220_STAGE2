#pragma once

#include <QVector2D>
#include <QPainter>

/**
 * @brief The Pocket class
 * @author nzho8446
 * @since Stage 2
 */
class Pocket {
public:
    Pocket(QVector2D pos, double radius);

    virtual ~Pocket();

    virtual void render(QPainter& painter);

    virtual QVector2D getPos();
    virtual double getRadius();

protected:
    QVector2D m_pos;
    double m_radius;
};
