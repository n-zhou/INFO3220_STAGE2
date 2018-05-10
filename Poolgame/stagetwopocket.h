#ifndef STAGETWOPOCKET_H
#define STAGETWOPOCKET_H

#include "pocket.h"

class StageTwoPocket : public Pocket
{
public:
    StageTwoPocket(QVector2D pos, double radius);

    ~StageTwoPocket() {}

    void render(QPainter &painter) override;
};

#endif // STAGETWOPOCKET_H
