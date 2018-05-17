#include "stagetwobuilder.h"

std::unique_ptr<AbstractPlayableGame> StageTwoBuilder::getResult() {

    if (m_buildingTable == nullptr) {
        throw std::invalid_argument("builder finished with no table supplied");
    }
    if (m_buildingBalls.empty()) {
        //no balls were built then we'll put a white one in the middle of the table
        m_buildingBalls.push_back(std::shared_ptr<Ball>(
                                      new StageTwoBall(QColor("White"), QVector2D(m_buildingTable->getWidth()/2, m_buildingTable->getHeight()/2),
                                                       QVector2D(0, 0), 1.0, 10, FLT_MAX)));
        std::cerr << "No balls provided, using default values..." << std::endl;
    }
    //we make a new variable to use in our lambda
    Table *t = m_buildingTable.get();
    //remove the balls that are out of bounds
    m_buildingBalls.erase(std::remove_if(
                              m_buildingBalls.begin(),
                              m_buildingBalls.end(),
                              [t](const std::shared_ptr<Ball> b)
                                { QVector2D pos = b->getPosition();
                                return pos.x() + b->getRadius() > t->getWidth() || pos.x() - b->getRadius() < 0
                                        || pos.y() + b->getRadius() > t->getHeight() || pos.y() - b->getRadius() < 0;}),
                          m_buildingBalls.end());

    std::unique_ptr<AbstractPlayableGame> retGame = std::unique_ptr<AbstractPlayableGame>(
                new StageTwoPlayableGame(std::move(m_buildingTable), m_buildingBalls));
    //need to reset for when we build next
    m_buildingBalls.clear();
    m_buildingTable = nullptr;
    return retGame;
}
