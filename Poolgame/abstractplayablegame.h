#pragma once

#include <QMouseEvent>
#include <QPainter>
#include <QKeyEvent>

class AbstractPlayableGame
{
public:
    AbstractPlayableGame() {}

    virtual ~AbstractPlayableGame() {}

    /**
     * @brief rightClick - this method should be called whenever
     * a there is a rightclick mouse event. The Default behaviour
     * of this method is to ignore it so it is recommended that subclasses
     * override this behaviour.
     *
     * @param e - The QMouseEvent associated with the rightclick
     */
    virtual void rightClick(QMouseEvent *e) {}

    /**
     * @brief rightClickRelease - this method is called whenever the rightclick
     * is released. The default behaviour of this class is to ignore it. As such
     * subclasses would override this defualt behaviour.
     * @param e - The QMouseEvent associated with releasing the right click
     */
    virtual void rightClickRelease(QMouseEvent *e) {}

    /**
     * @brief leftClick - this method should be called whenever
     * a there is a leftclick mouse event. The Default behaviour
     * of this method is to ignore it so it is recommended that subclasses
     * override this behaviour.
     *
     * @param e - The QMouseEvent associated with releasing the left click
     */
    virtual void leftClick(QMouseEvent *e) {}

    /**
     * @brief leftClickRelease - this method is called whenever the
     * left mouse button is released.
     *
     * @param e - The QMouseEvent associated with the releasing the
     * leftclick.
     */
    virtual void leftClickRelease(QMouseEvent *e) {}

    /**
     * @brief mouseDrag - this method is called whenever the user drags their
     * mouse while holding left click. Subclassses are recommended to override
     * this default behaviour.
     */
    virtual void mouseDrag(QMouseEvent *e) {}

    /**
     * @brief keyPressEvent - called whenever the user hits a key on their
     * keyboard
     *
     * @param event - the QKeyEvent associated with the keypress
     */
    virtual void keyPressEvent(QKeyEvent *event) {}

    /**
     * @brief keyReleaseEvent - called whenever the user releases
     * a keypress.
     *
     * @param event - the QKeyEvent associated with the key release
     */
    virtual void keyReleaseEvent(QKeyEvent *event) {}


    /**
     * @brief render - Draws the game onto the screen
     * @param painter - QPainter used to draw the objects with
     */
    virtual void render(QPainter &painter) = 0;

    /**
     * @brief animate - applys the physics to the game based on
     * the paramater
     * @param dt -
     */
    virtual void animate(double dt) = 0;

    /**
     * @brief getMinimumHeight
     *
     * @return the minimum height required for the window
     * to be to display the objects in the game
     */
    virtual int getMinimumHeight() const = 0;

    /**
     * @brief getMinimumWidth
     *
     * @return the minimum width requried for the window
     * to be to display the objects in the game
     */
    virtual int getMinimumWidth() const = 0;


};
