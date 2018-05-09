#pragma once

#include "stagetwoplayablegame.h"
#include "table.h"

/**
 * @brief The StageTwoTable class
 *
 * @author nzho8446
 * @since Stage 2
 * @see Table
 */

class StageTwoTable : public Table {
public:
    StageTwoTable(int width, int height, QColor colour, double friction,
                   std::vector<std::shared_ptr<Pocket>> &pockets)
        : Table(width, height, colour, friction, pockets){}

    void render(QPainter& painter);
protected:

};
