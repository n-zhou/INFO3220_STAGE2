#pragma once

#include "stagetwoplayablegame.h"
#include "table.h"

class StageTwoTable : public Table
{
public:
    StageTwoTable(int width, int height, QColor colour, double friction,
                   std::vector<std::shared_ptr<Pocket>> &pockets)
        : Table(width, height, colour, friction, pockets){}

    void render(QPainter& painter);

};
