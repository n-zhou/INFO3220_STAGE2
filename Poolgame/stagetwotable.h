#ifndef STAGETWOTABLE_H
#define STAGETWOTABLE_H

#include "table.h"

class StageTwoTable : Table
{
public:
    StageTwoTable(int width, int height, QColor colour, double friction,
                   std::vector<std::shared_ptr<Pocket>> pockets)
        : Table(width, height, colour, friction, pockets){}

    void render(QPainter& painter);
};

#endif // STAGETWOTABLE_H
