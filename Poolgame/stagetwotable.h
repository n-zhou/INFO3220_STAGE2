#pragma once

#include "stagetwoplayablegame.h"
#include "table.h"

/**
 * @brief The StageTwoTable class is can do everthing StageOneTable can and
 * draw pockets as well. Isn't that cool?
 *
 * @author nzho8446
 * @see Table
 * @see StageOneTable
 * @since Stage 2
 */

class StageTwoTable : public Table {
public:
    StageTwoTable(int width, int height, QColor colour, double friction,
                   std::vector<std::unique_ptr<Pocket>> &pockets)
        : Table(width, height, colour, friction, pockets){}

    void render(QPainter& painter) override;
};
