#ifndef POCKET_H
#define POCKET_H

#include <QVector2D>
#include <QPainter>

class Pocket
{
public:
    Pocket(QVector2D pos, double radius);

    ~Pocket();

    virtual void render(QPainter& painter);

    QVector2D getPos();
    double getRadius();

protected:
    QVector2D m_pos;
    double m_radius;
};

#endif // POCKET_H
