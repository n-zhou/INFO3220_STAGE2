
#include "abstractplayablegame.h"
#include "stageoneadaptor.h"
#include "gamebuilder.h"
#include "game.h"
#include <iostream>
#include <QJsonArray>

StageOneBuilder::~StageOneBuilder() {

}

void StageOneBuilder::addBall(QJsonObject &ballData) {
    m_buildingBalls.push_back(std::move(m_factory->makeBall(ballData)));
}

void StageOneBuilder::addTable(QJsonObject &tableData) {
    // ensure that we haven't already created another table
    if (m_buildingTable != nullptr) throw std::invalid_argument("table created twice");
    m_buildingTable = m_factory->makeTable(tableData);
}

AbstractPlayableGame* StageOneBuilder::getResult() {

    // likewise for table
    if (m_buildingTable == nullptr) {
        throw std::invalid_argument("builder finished with no table supplied");
    }

    Game* retGame = new Game(m_buildingBalls, m_buildingTable);
    // need to reset for when we build next
    m_buildingBalls.clear();
    m_buildingTable = nullptr;
    return new StageOneAdaptor(retGame);
}

AbstractPlayableGame* GameDirector::createGame() {
    // construct our table
    QJsonObject tableData = m_conf->value("table").toObject();
    m_builder->addTable(tableData);

    // for each of our balls, construct them
    QJsonArray ballData = m_conf->value("balls").toArray();
    for (const auto& item : ballData) {
        QJsonObject t = item.toObject();
        m_builder->addBall(t);
    }

    return m_builder->getResult();
}
