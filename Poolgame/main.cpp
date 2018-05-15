/**
  * Written by James Butcher
  * 2018/04/12
  *
  * <p>
  * This code has been inherited from "James Butcher" and modified
  * for the purpose of <tt>INFO3220 Assignment 2<ttl>.
  * </p>
  *
  * <p>
  * A major modification to this code base is the conversion of
  * using raw pointers to using smart pointers. While raw pointers
  * are still present in many methods, they are not returned from
  * any method. This should aid the programmer with working out
  * ownership of a pointer.
  * </p>
  *
  * @author nzho8446
  * @since Stage 1
  * @see Cameron Hosking
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

int main(int argc, char *argv[]) {
    QJsonObject conf = loadConfig();
    if (conf.contains("stage2") && !conf["stage2"].isBool()) {
        std::cerr << "Invalid Stage 2 value, setting to Stage 1" << std::endl;
    }
    bool stage2 = (!conf.contains("stage2") || !conf["stage2"].toBool()) ? false : true;
    // create our game based on our config
    GameDirector director(&conf);
    /* set and transfer ownership of this builder to the director.
     * we choose the builder based on whether the config file is a
     * stage 2 config file. */
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
