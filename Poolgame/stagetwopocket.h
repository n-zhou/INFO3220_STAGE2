#ifndef STAGETWOPOCKET_H
#define STAGETWOPOCKET_H

#include "pocket.h"

/**
 * @brief The StageTwoPocket class provides a concrete implementation
 * of the Pocket interface
 *
 * @author nzho8446
 * @since Stage 2
 */

class StageTwoPocket : public Pocket
{
public:
    StageTwoPocket(QVector2D pos, double radius);

    virtual ~StageTwoPocket() {}

    virtual void render(QPainter &painter) override;
};

#endif // STAGETWOPOCKET_H
