#pragma once

#include <QColor>
#include <QPainter>
#include <vector>
#include <memory>
#include "pocket.h"


/**
 * @brief The Table class represents a pool table in the game of
 * billards or as most people call it, pool.
 *
 * <p>
 * Since stage 2, the Table contains pockets as well.
 * </p>
 *
 * @author "James Butcher"
 * @author nzho8446
 * @see StageOneTable
 * @see StageTwoTable
 * @since Stage 1
 */
class Table {
protected:
    int m_width;
    int m_height;
    int m_xpos;
    int m_ypos;
    std::vector<std::unique_ptr<Pocket>> m_pockets;
    QBrush m_brush;
    const double m_friction;

public:
    virtual ~Table() {}

    //default values added since stage 2
    Table(int width, int height, QColor colour, double friction, int xpos = 0, int ypos = 0) :
        m_width(width), m_height(height), m_xpos(xpos), m_ypos(ypos),
        m_pockets(), m_brush(colour), m_friction(friction) {}

    //constructor available since stage 2
    Table(int width, int height, QColor colour, double friction,
          std::vector<std::unique_ptr<Pocket>> &pockets, int xpos = 0, int ypos = 0) :
        m_width(width), m_height(height), m_xpos(xpos), m_ypos(ypos),
        m_pockets(std::move(pockets)), m_brush(colour), m_friction(friction) {}

    /**
     * @brief render - draw the table to screen using the specified painter
     * @param painter - painter to use
     */
    virtual void render(QPainter& painter) = 0;

    /**
     * @brief addPocket - adds a pocket to this table
     * @param pocket - the pocket to add
     */
    void addPocket(std::unique_ptr<Pocket> pocket) { m_pockets.push_back(std::move(pocket)); }

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getX() const { return m_xpos; }
    int getY() const { return m_ypos; }
    double getFriction() const { return m_friction; }
    const std::vector<std::unique_ptr<Pocket>> &getPockets() const { return m_pockets; }
};

/**
 * @brief The StageOneTable class provides a simple but concrete implementation of Table.
 * @author "James Butcher"
 * @since Stage 1
 */
class StageOneTable : public Table {
public:
    StageOneTable(int width, int height, QColor colour, double friction) :
        // table isn't translated anywhere - starts at (0,0)
        Table(width, height, colour, friction, 0, 0) {}
    /**
     * @brief render - draw the stageonetable to screen using the specified painter
     * @param painter - painter to use
     */
    void render(QPainter &painter) override;
};
