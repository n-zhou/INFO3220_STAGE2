#pragma once

#include <QMouseEvent>
#include <QPainter>

class AbstractPlayableGame
{
public:
    AbstractPlayableGame(Game *game){}

    virtual AbstractPlayableGame(){}

    /**
     * @brief rightClick - this method should be called whenever
     * a there is a rightclick mouse event. The Default behaviour
     * of this method is to ignore it so it is recommended that subclasses
     * override this behaviour.
     *
     * @param e - The QMouseEvent associated with the rightclick
     */
    virtual void rightClick(QMouseEvent &e) {}

    /**
     * @brief rightClickRelease - this method is called whenever the rightclick
     * is released. The default behaviour of this class is to ignore it. As such
     * subclasses would override this defualt behaviour.
     * @param e - The QMouseEvent associated with releasing the rightclick
     */
    virtual void rightClickRelease(QMouseEvent &e) {}

    /**
     * @brief leftClick - this method should be called whenever
     * a there is a leftclick mouse event. The Default behaviour
     * of this method is to ignore it so it is recommended that subclasses
     * override this behaviour.
     */
    virtual void leftClick(QMouseEvent &e) {}

    /**
     * @brief leftClickRelease - this method is called whenever the
     * left mouse button is released.
     * @param e - The QMouseEvent associated with the releasing the
     * leftclick.
     */
    virtual void leftClickRelease(QMouseEvent &e);

    /**
     * @brief mouseDrag - this method is called whenever the user drags their
     * mouse while holding left click. Subclassses are recommended to override
     * this default behaviour.
     */
    virtual void mouseDrag(QMouseEvent &e) {}

    /**
     * @brief render - Draws the game onto the screen
     * @param painter - QPainter used to draw the objects with
     */
    virtual void render(QPainter &painter) = 0;

protected:

};
