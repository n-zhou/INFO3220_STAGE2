#ifndef POCKET_H
#define POCKET_H

#include <QVector2D>
#include <QPainter>

class Pocket
{
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

#endif // POCKET_H
