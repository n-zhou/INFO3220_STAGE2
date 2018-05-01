#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QTimer>
#include <iostream>
#include "utils.h"

//nzho8446 added headers
#include <QMouseEvent>
#include <cmath>

Dialog::Dialog(Game *game, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_game(game)
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
    this->resize(game->getMinimumWidth(), game->getMinimumHeight());

    progress_bar = new QProgressBar(this);
    progress_bar->setVisible(true);
    progress_bar->resize(game->getMinimumWidth(), 20);
    progress_bar->move(0, game->getMinimumHeight());
    progress_bar->setAlignment(Qt::AlignCenter);
    this->resize(game->getMinimumWidth(), game->getMinimumHeight() + 20);
    this->setMouseTracking(true);
    progress_bar->setValue(0);


}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() ==  Qt::LeftButton) {
        progress_bar->setVisible(true);
        on = true;
        x = event->x();
        y = event->y();
    }


}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if (on) {
            progress_bar->reset();
            progress_bar->setVisible(false);
            on = false;
        }
    }
}

#include <QVector2D>
void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    if (on) {
        QVector2D clickPos(event->x(), event->y());
        QVector2D original(x, y);
        progress_bar->setValue(std::fmin(clickPos.distanceToPoint(original)/3, 100));
    }
}

Dialog::~Dialog()
{
    delete aTimer;
    delete dTimer;
    delete m_game;
    delete ui;
}

void Dialog::tryRender() {
    this->update();
}

void Dialog::nextAnim() {
    m_game->animate(1.0/(double)animFrameMS);
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    m_game->render(painter);
}
