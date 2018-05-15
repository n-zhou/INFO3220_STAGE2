#pragma once
#include <QDialog>
#include "abstractplayablegame.h"
#include "ball.h"
#include "game.h"

//nzho8446 added headers


namespace Ui {
class Dialog;
}

/**
 * @brief The Dialog class creates the window that displays the pool game.
 *
 * <p>
 * Since stage 2, the dialog class sends mouse and keyboard events to a new game class
 * (AbstractPlayableGame). The member variable m_game is now a smart pointer instead of a
 * raw pointer. The rest of the member variable raw pointers were not changed to smart
 * pointers because it is clear that they are only visible to the dialog class.
 * </p>
 *
 * <p>
 * The constuctor was also modified to take a smart pointer instead of a raw pointer.
 * </p>
 * @author "James Butcher"
 * @author nzho8446
 * @version Stage 2
 * @since Stage 1
 */

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(std::unique_ptr<AbstractPlayableGame> game, QWidget *parent = 0);
    ~Dialog();

protected:
    /**
     * @brief paintEvent - called whenever window repainting is requested
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief mousePressEvent - called whenever the user clicks their mouse
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief mouseReleaseEvent - called whenever the user releases their click
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief mouseReleaseEvent - called whenever the user moves the mouse
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief keyPressEvent - called whenever the user hits a key
     * @param event - the QKeyEvent associated with the keypress
     */
    void keyPressEvent(QKeyEvent *event);
public slots:
    /**
     * @brief nextAnim - move the objects and perform collision events
     */
    void nextAnim();
    /**
     * @brief tryRender - draw the objects to screen
     */
    void tryRender();

private:
    /**
     * @brief aTimer - timer for calling nextAnim in intervals
     */
    QTimer* aTimer = nullptr;
    /**
     * @brief dTimer - timer for calling tryRender in intervals
     */
    QTimer* dTimer = nullptr;
    /**
     * @brief ui our drawable ui
     */
    Ui::Dialog *ui;
    /**
     * @brief m_game - our game object to be played
     */
    std::unique_ptr<AbstractPlayableGame> m_game;

};

