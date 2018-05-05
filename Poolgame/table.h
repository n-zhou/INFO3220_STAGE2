#pragma once

#include <QColor>
#include <QPainter>
#include <vector>
#include <memory>
#include "pocket.h"

class Table {
protected:
    int m_width;
    int m_height;
    int m_xpos;
    int m_ypos;
    QBrush m_brush;
    double m_friction;

    std::vector<std::shared_ptr<Pocket>> m_pockets;

public:
    virtual ~Table() {}
    Table(int width, int height, QColor colour, double friction, int xpos = 0, int ypos = 0) :
        m_width(width), m_height(height), m_xpos(xpos), m_ypos(ypos),
        m_brush(colour), m_friction(friction) {}

    Table(int width, int height, QColor colour, double friction,
          std::vector<std::shared_ptr<Pocket>> pockets, int xpos = 0, int ypos = 0) :
        m_width(width), m_height(height), m_xpos(xpos), m_ypos(ypos), m_pockets(pockets),
        m_brush(colour), m_friction(friction) {}

    /**
     * @brief render - draw the table to screen using the specified painter
     * @param painter - painter to use
     */
    virtual void render(QPainter& painter) = 0;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getX() const { return m_xpos; }
    int getY() const { return m_ypos; }
    double getFriction() const { return m_friction; }
    std::vector<std::shared_ptr<Pocket>> getPockets() const { return m_pockets; }
};

class StageOneTable : public Table
{
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
