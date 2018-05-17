#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <QMouseEvent>
#include <utility>
#include "utils.h"

Dialog::Dialog(std::unique_ptr<AbstractPlayableGame> game, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_game(std::move(game))
{
    this->setWindowTitle("Cameron please give me 100%");
    ui->setupUi(this);

    // for animating (i.e. movement, collision) every animFrameMS
    aTimer = new QTimer(this);
    connect(aTimer, SIGNAL(timeout()), this, SLOT(nextAnim()));
    aTimer->start(animFrameMS);

    // for drawing every drawFrameMS milliseconds
    dTimer = new QTimer(this);
    connect(dTimer, SIGNAL(timeout()), this, SLOT(tryRender()));
    dTimer->start(drawFrameMS);
    // set the window size to be at least the table size
    this->resize(m_game->getMinimumWidth(), m_game->getMinimumHeight());
    this->setMouseTracking(false);



}

void Dialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_game->leftClick(event);
    } else if (event->button() == Qt::RightButton) {
        m_game->rightClick(event);
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_game->leftClickRelease(event);
    } else if (event->button() == Qt::RightButton) {
        m_game->rightClickRelease(event);
    }
}

void Dialog::mouseMoveEvent(QMouseEvent *event) {
    m_game->mouseDrag(event);
}

void Dialog::keyPressEvent(QKeyEvent *event) {
    m_game->keyPressEvent(event);
}

Dialog::~Dialog() {
    delete aTimer;
    delete dTimer;
    delete ui;
}

void Dialog::tryRender() {
    this->update();
}

void Dialog::nextAnim() {
    m_game->animate(animFrameMS/1000.0);
}

void Dialog::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    m_game->render(painter);
}
