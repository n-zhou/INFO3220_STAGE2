/**
  * Written by James Butcher
  * 2018/04/12
  *
  * @author Not James Butcher
  *
  */

#include "dialog.h"
#include "game.h"
#include "utils.h"
#include "gamebuilder.h"
#include "stagetwobuilder.h"
#include "ball.h"
#include <QApplication>
#include <QFile>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <utility>

QJsonObject loadConfig() {
    // load json from config file
    QFile conf_file(config_path);
    conf_file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString content = conf_file.readAll();
    conf_file.close();
    QJsonObject config = QJsonDocument::fromJson(content.toUtf8()).object();
    return config;
}

bool Ball::toggle = false;

int main(int argc, char *argv[])
{
    QJsonObject conf = loadConfig();
    bool stage2 = (!conf.contains("stage2") || !conf["stage2"].toBool()) ? false : true;
    // create our gambased on our config
    GameDirector director(&conf);
    // set and transfer ownership of this builder to the director,
    director.setBuilder(stage2 ? new StageTwoBuilder() : new StageOneBuilder());
    std::unique_ptr<AbstractPlayableGame> game = director.createGame();

    // display our dialog that contains our game and run
    QApplication a(argc, argv);
    Dialog w(std::move(game), nullptr);
    if (stage2)
        w.setFixedSize(w.size());
    w.show();

    return a.exec();
}
